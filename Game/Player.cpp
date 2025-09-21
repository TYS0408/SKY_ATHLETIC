#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	//アニメーションクリップを読み込む
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
//移動処理
Move();

//回転処理
Rotation();
//ステート管理
ManageState();

//アニメーション再生
PlayAnimation();

	
	//回転を絵描きさんに教える
	//m_modelRender.SetRotation(rot);
	m_modelRender.Update();
}
void Player::Manager()
{
	
}

void Player::Move()
{
	//xzの移動処理を0.0fにする
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;

	//左スティックの入力量を取得
	Vector3 stickL;
	stickL.x = g_pad[0]->GetLStickXF();
	stickL.y = g_pad[0]->GetLStickYF();
	//移動速度にスティックの入力量を加算
	m_moveSpeed.x += stickL.x * 120.0f;
	m_moveSpeed.z += stickL.y * 120.0f;

	//カメラの前方向と右方向のベクトルを持ってくる
	Vector3 forward = g_camera3D->GetForward();
	Vector3 right = g_camera3D->GetRight();

	//Vector3 forward(0.0f, 0.0f, 1.0f); // Z方向を前にする
	//Vector3 right(1.0f, 0.0f, 0.0f);   // X方向を右にする
	//y方向には移動させない
	forward.y = 0.0f;
	right.y = 0.0f;

	//正規化
	forward.y = 0.0f;
	forward.Normalize();
	right.y = 0.0f;
	right.Normalize();

	// 入力量を反映（TPS方式）
	Vector3 moveDir = forward * stickL.y * 120.0f + right * stickL.x * 120.0f;
	m_moveSpeed.x = moveDir.x;
	m_moveSpeed.z = moveDir.z;

	////左スティックの入力量と120.0fを乗算する
	right *= stickL.x * 120.0f;
	forward *= stickL.y * 120.0f;

	////移動速度に上記で計算したベクトルを加算
	m_moveSpeed += right + forward;





	if (m_characterController.IsOnGround())
	{
		m_moveSpeed.y = 0.0f;
		//ダッシュ処理を「もし地面についていなかったら」
		//というif文の中に入れてないとダッシュした時にジャンプにも
		// *2されてしまいおかしくなる
		//ダッシュ処理
		if (g_pad[0]->IsPress(enButtonB))
		{
			m_moveSpeed.x *= 2.0f;
			m_moveSpeed.z *= 2.0f;
		}

		//ジャンプ処理
		if (g_pad[0]->IsTrigger(enButtonA))
		{
			m_moveSpeed.y += 550.0f;
			//m_moveSpeed.y += 2000.0f;
		}
	}
	//重力処理(地面についていなかったら)
	else
	{
		m_moveSpeed.y -= 5.0f * 2.0f;
		//m_moveSpeed.y -= 8.0f * 2.0f;
	}
	//リスポーン処理	
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
		//地面についた。
		m_moveSpeed.y = 0.0f; }
	//キャラクターコントローラーを使って座標を移動させる。
	
	
	//絵描きさんに座標を教える
	m_modelRender.SetPosition(m_position);

	
}


void Player::Rotation()
{
	if (fabsf(m_moveSpeed.x) >= 0.001f || fabsf(m_moveSpeed.z) >= 0.001f)
		////////↑絶対値を取る値
	{
		//キャラクターの方向を変える
		m_rot.SetRotationYFromDirectionXZ(m_moveSpeed);
		//絵描きさんに回転を教える
		m_modelRender.SetRotation(m_rot);
	}

}

void Player::ManageState()
{
	//地面についていなかったら
	if (m_characterController.IsOnGround() == false)
	{
		//ステートをジャンプにする
		m_PlayerState = 2;
		//ここでManageState関数の処理を終わらせる
		return;
	}

	//地面についていたら
	//xかzの移動処理があったら

	//ダッシュしていたら
	if (fabsf(m_moveSpeed.x) >= 0.001 || fabsf(m_moveSpeed.z) >= 0.001f)
	{
		if (g_pad[0]->IsPress(enButtonB))
		{
			//ステートを走りにする
			m_PlayerState = 3;
		}
		else
		{
			//ステートを歩きにする
			m_PlayerState = 1;
		}
	}

	//xとzの移動処理がなかったら
	else
	{
		//ステートを待機にする
		m_PlayerState = 0;
	}
}

	
	





void Player::PlayAnimation()
{
	//アニメーション再生
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
//	//このフレームの移動量を求める。
//	//左スティックの入力量を受け取る。
//	float lStick_x = g_pad[0]->GetLStickXF();
//	float lStick_y = g_pad[0]->GetLStickYF();
//	//カメラの前方方向と右方向を取得。
//	Vector3 cameraForward = g_camera3D->GetForward();
//	Vector3 cameraRight = g_camera3D->GetRight();
//	//XZ平面での前方方向、右方向に変換する。
//	cameraForward.y = 0.0f;
//	cameraForward.Normalize();
//	cameraRight.y = 0.0f;
//	cameraRight.Normalize();
//	//XZ成分の移動速度をクリア。
//	m_moveSpeed += cameraForward * lStick_y * 500.0f;	//奥方向への移動速度を加算。
//	m_moveSpeed += cameraRight * lStick_x * 500.0f;		//右方向への移動速度を加算。
//
//	if (g_pad[0]->IsTrigger(enButtonA) //Aボタンが押されたら
//		&& m_characterController.IsOnGround()  //かつ、地面に居たら
//		) {
//		//ジャンプする。
//		m_moveSpeed.y = 1000.0f;	//上方向に速度を設定して、
//	}
//
//	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
//	//キャラクターコントローラーを使用して、座標を更新。
//
//	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
//	if (m_characterController.IsOnGround()) {
//		//地面についた。
//		m_moveSpeed.y = 0.0f;
//	}
//
//	//座標を設定。
//	m_modelRender.SetPosition(m_position);
//
//	//ここで0にする。
//	m_moveSpeed.x = 0.0f;
//	m_moveSpeed.z = 0.0f;
//}
//
//void Player::Render(RenderContext& rc)
//{
//	m_modelRender.Draw(rc);
//}
