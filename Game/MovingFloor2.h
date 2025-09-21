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
		//座標を設定
		//<param name= "position">座標。</param>
		void SetPosition(const Vector3& position)
		{
			m_movePosition2 = position;
		}
		Vector3 m_movePosition2;
		Vector3 m_firstPosition2;
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


