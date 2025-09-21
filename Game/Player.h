#pragma once
class MovingFloor;
class Player: public IGameObject
{
public:
	Player();
	~Player();
	bool Start();
	void Update();
	void Manager();
	void Render(RenderContext& rc);
	void Move();
	void Rotation();
	void ManageState();
	void PlayAnimation();
	
	const Vector3& GetPosition() const
	{
		return m_position;
	}

	//<summary>
	// �ړ����x�����Z
	// <summary>
	void AddPosition(const Vector3& delta);
	
	//<summary>
	//�L�����N�^�[�R���g���[���[���擾
	//<summary>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}

	
	int m_ItemCount = 0;
	Vector3 m_position; //���W
	//�������烁���o�ϐ�
private:
	
	ModelRender m_modelRender;
	Quaternion m_rot; //��]
	int m_PlayerState = 0;//�v���C���[�X�e�[�g
	enum EnPlayAnimation
	{
      enAnimationClip_Idle,
	  enAnimationClip_Walk,
	  enAnimationClip_Jump,
	  enAnimationClip_Run,
	  enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];
	CharacterController m_characterController;//�L�����N�^�[�R���g���[���[
	Vector3 m_moveSpeed = Vector3::Zero; //�ړ�����
	Vector3  m_respawn; //���X�|�[������
	MovingFloor* m_movingfloor;
	
	

};

