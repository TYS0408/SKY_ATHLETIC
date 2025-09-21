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
	//���W��ݒ�
	//<param name= "position">���W�B</param>
	void SetPosition(const Vector3& position)
	{
		m_movePosition = position;
	}
	Vector3 m_movePosition;
	Vector3 m_firstPosition;
	Vector3 m_prevPosition = Vector3::Zero;
private:
	//<summary>
	//<�ړ�����>
	//<summary>
	void Move();
	
	
	ModelRender m_movingmodelRender;
	Player* m_player = nullptr;
	PhysicsStaticObject  m_PhysicsStaticObject; //�ÓI�����I�u�W�F�N�g
	CollisionObject* m_collisionObject = nullptr; //�R���W�����I�u�W�F�N�g

	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,
		enMovingFloorState_MovingLeft
	};
	enMovingFloorState  m_MovingFloorState = enMovingFloorState_MovingRight;
};






