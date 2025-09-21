#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//�A�j���[�V�����N���b�v��ǂݍ���
	animationClips[enAnimationClip_Idle].Load("Assets/animData/idle.tka");
	animationClips[enAnimationClip_Idle].SetLoopFlag(true);
	animationClips[enAnimationClip_Walk].Load("Assets/animData/walk.tka");
	animationClips[enAnimationClip_Walk].SetLoopFlag(true);
	animationClips[enAnimationClip_Jump].Load("Assets/animData/jump.tka");
	animationClips[enAnimationClip_Jump].SetLoopFlag(false);
	animationClips[enAnimationClip_Run].Load("Assets/animData/run.tka");
	animationClips[enAnimationClip_Run].SetLoopFlag(true);
	m_modelRender.Init("Assets/modelData/unityChan.tkm",animationClips,enAnimationClip_Num,enModelUpAxisY);
	
	m_position = Vector3(0.0f, 0.0f, -800.0f);
	m_characterController.Init(25.0f, 75.0f, m_position);

}

Player::~Player()
{

}

bool Player::Start()
{
	m_respawn = m_position;
	return true;
}

void Player::AddPosition(const Vector3& delta)
{
	m_position += delta;
	m_characterController.SetPosition(m_position);
}

void Player::Update()
{
//Manager();
//�ړ�����
Move();

//��]����
Rotation();
//�X�e�[�g�Ǘ�
ManageState();

//�A�j���[�V�����Đ�
PlayAnimation();

	
	//��]���G�`������ɋ�����
	//m_modelRender.SetRotation(rot);
	m_modelRender.Update();
}
void Player::Manager()
{
	
}

void Player::Move()
{
	//xz�̈ړ�������0.0f�ɂ���
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//���X�e�B�b�N�̓��͗ʂ��擾
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	//�ړ����x�ɃX�e�B�b�N�̓��͗ʂ����Z
	m_moveSpeed.x += stickL.x * 120.0f;
	m_moveSpeed.z += stickL.y * 120.0f;

	//�J�����̑O�����ƉE�����̃x�N�g���������Ă���
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//Vector3 forward(0.0f, 0.0f, 1.0f); // Z������O�ɂ���
	//Vector3 right(1.0f, 0.0f, 0.0f);   // X�������E�ɂ���
	//y�����ɂ͈ړ������Ȃ�
	forward.y = 0.0f;
	right.y = 0.0f;

	//���K��
	forward.y = 0.0f;
	forward.Normalize();
	right.y = 0.0f;
	right.Normalize();

	// ���͗ʂ𔽉f�iTPS�����j
	Vector3 moveDir = forward * stickL.y * 120.0f + right * stickL.x * 120.0f;
	m_moveSpeed.x = moveDir.x;
	m_moveSpeed.z = moveDir.z;

	////���X�e�B�b�N�̓��͗ʂ�120.0f����Z����
	right *= stickL.x * 120.0f;
	forward *= stickL.y * 120.0f;

	////�ړ����x�ɏ�L�Ōv�Z�����x�N�g�������Z
	m_moveSpeed += right + forward;





	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;
		//�_�b�V���������u�����n�ʂɂ��Ă��Ȃ�������v
		//�Ƃ���if���̒��ɓ���ĂȂ��ƃ_�b�V���������ɃW�����v�ɂ�
		// *2����Ă��܂����������Ȃ�
		//�_�b�V������
		if (g_pad[0]->IsPress(enButtonB))
		{
			m_moveSpeed.x *= 2.0f;
			m_moveSpeed.z *= 2.0f;
		}

		//�W�����v����
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_moveSpeed.y += 550.0f;
			//m_moveSpeed.y += 2000.0f;
		}
	}
	//�d�͏���(�n�ʂɂ��Ă��Ȃ�������)
	else
	{
		m_moveSpeed.y -= 5.0f * 2.0f;
		//m_moveSpeed.y -= 8.0f * 2.0f;
	}
	//���X�|�[������	
	if (m_position.y <= -500.0f)
	{
		m_position = m_respawn;
		m_moveSpeed = Vector3::Zero;
		m_characterController.SetPosition(m_position);
		m_modelRender.SetPosition(m_position);
	}
	
	//m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_characterController.IsOnGround()) 
	{
		//�n�ʂɂ����B
		m_moveSpeed.y = 0.0f; }
	//�L�����N�^�[�R���g���[���[���g���č��W���ړ�������B
	
	
	//�G�`������ɍ��W��������
	m_modelRender.SetPosition(m_position);

	
}


void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
		////////����Βl�����l
	{
		//�L�����N�^�[�̕�����ς���
		m_rot.SetRotationYFromDirectionXZ(m_moveSpeed);
		//�G�`������ɉ�]��������
		m_modelRender.SetRotation(m_rot);
	}

}

void Player::ManageState()
{
	//�n�ʂɂ��Ă��Ȃ�������
	if (m_characterController.IsOnGround() == false)
	{
		//�X�e�[�g���W�����v�ɂ���
		m_PlayerState = 2;
		//������ManageState�֐��̏������I��点��
		return;
	}

	//�n�ʂɂ��Ă�����
	//x��z�̈ړ���������������

	//�_�b�V�����Ă�����
	if (fabsf(m_moveSpeed.x) >= 0.001 || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		if (g_pad[0]->IsPress(enButtonB))
		{
			//�X�e�[�g�𑖂�ɂ���
			m_PlayerState = 3;
		}
		else
		{
			//�X�e�[�g������ɂ���
			m_PlayerState = 1;
		}
	}

	//x��z�̈ړ��������Ȃ�������
	else
	{
		//�X�e�[�g��ҋ@�ɂ���
		m_PlayerState = 0;
	}
}

	
	





void Player::PlayAnimation()
{
	//�A�j���[�V�����Đ�
	switch (m_PlayerState)
	{
	case 0:
		m_modelRender.PlayAnimation(enAnimationClip_Idle);
		break;

	case 1:
		m_modelRender.PlayAnimation(enAnimationClip_Walk);
		break;

	case 2:
		m_modelRender.PlayAnimation(enAnimationClip_Jump);
		break;

	case 3:
		m_modelRender.PlayAnimation(enAnimationClip_Run);
		break;

	}
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}




//bool Player::Start()
//{
//	m_modelRender.Init("Assets/modelData/unityChan.tkm");
//	m_characterController.Init(20.0f,
//		100.0f,
//		m_position);
//	return true;
//}
//
//void Player::Update()
//{
//	Move();
//
//	m_modelRender.Update();
//}
//
//void Player::Move()
//{
//	//���̃t���[���̈ړ��ʂ����߂�B
//	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
//	float lStick_x = g_pad[0]->GetLStickXF();
//	float lStick_y = g_pad[0]->GetLStickYF();
//	//�J�����̑O�������ƉE�������擾�B
//	Vector3 cameraForward = g_camera3D->GetForward();
//	Vector3 cameraRight = g_camera3D->GetRight();
//	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
//	cameraForward.y = 0.0f;
//	cameraForward.Normalize();
//	cameraRight.y = 0.0f;
//	cameraRight.Normalize();
//	//XZ�����̈ړ����x���N���A�B
//	m_moveSpeed += cameraForward * lStick_y * 500.0f;	//�������ւ̈ړ����x�����Z�B
//	m_moveSpeed += cameraRight * lStick_x * 500.0f;		//�E�����ւ̈ړ����x�����Z�B
//
//	if (g_pad[0]->IsTrigger(enButtonA) //A�{�^���������ꂽ��
//		&& m_characterController.IsOnGround()  //���A�n�ʂɋ�����
//		) {
//		//�W�����v����B
//		m_moveSpeed.y = 1000.0f;	//������ɑ��x��ݒ肵�āA
//	}
//
//	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
//	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B
//
//	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
//	if (m_characterController.IsOnGround()) {
//		//�n�ʂɂ����B
//		m_moveSpeed.y = 0.0f;
//	}
//
//	//���W��ݒ�B
//	m_modelRender.SetPosition(m_position);
//
//	//������0�ɂ���B
//	m_moveSpeed.x = 0.0f;
//	m_moveSpeed.z = 0.0f;
//}
//
//void Player::Render(RenderContext& rc)
//{
//	m_modelRender.Draw(rc);
//}
