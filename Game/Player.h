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
	// 移動速度を加算
	// <summary>
	void AddPosition(const Vector3& delta);
	
	//<summary>
	//キャラクターコントローラーを取得
	//<summary>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}

	
	int m_ItemCount = 0;
	Vector3 m_position; //座標
	//ここからメンバ変数
private:
	
	ModelRender m_modelRender;
	Quaternion m_rot; //回転
	int m_PlayerState = 0;//プレイヤーステート
	enum EnPlayAnimation
	{
      enAnimationClip_Idle,
	  enAnimationClip_Walk,
	  enAnimationClip_Jump,
	  enAnimationClip_Run,
	  enAnimationClip_Num,
	};
	AnimationClip animationClips[enAnimationClip_Num];
	CharacterController m_characterController;//キャラクターコントローラー
	Vector3 m_moveSpeed = Vector3::Zero; //移動処理
	Vector3  m_respawn; //リスポーン処理
	MovingFloor* m_movingfloor;
	
	

};

