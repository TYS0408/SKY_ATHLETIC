#pragma once
class Player;
class MovingFloor2: public IGameObject
{
	public:
		MovingFloor2();
		~MovingFloor2();
		bool Start() override;
		void Update() override;
		void Render(RenderContext& rc)override;
		//<summary>
		//���W��ݒ�
		//<param name= "position">���W�B</param>
		void SetPosition(const Vector3& position)
		{
			m_movePosition2 = position;
		}
		Vector3 m_movePosition2;
		Vector3 m_firstPosition2;
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


