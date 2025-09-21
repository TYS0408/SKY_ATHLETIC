#pragma once
class Player;
class MovingFloor : public IGameObject
{
public:
	MovingFloor();
	~MovingFloor();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc)override;
	//<summary>
	//座標を設定
	//<param name= "position">座標。</param>
	void SetPosition(const Vector3& position)
	{
		m_movePosition = position;
	}
	Vector3 m_movePosition;
	Vector3 m_firstPosition;
	Vector3 m_prevPosition = Vector3::Zero;
private:
	//<summary>
	//<移動処理>
	//<summary>
	void Move();
	
	
	ModelRender m_movingmodelRender;
	Player* m_player = nullptr;
	PhysicsStaticObject  m_PhysicsStaticObject; //静的物理オブジェクト
	CollisionObject* m_collisionObject = nullptr; //コリジョンオブジェクト

	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,
		enMovingFloorState_MovingLeft
	};
	enMovingFloorState  m_MovingFloorState = enMovingFloorState_MovingRight;
};






