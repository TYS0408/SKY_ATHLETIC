#include "stdafx.h"
#include "MovingFloor.h"
#include"Player.h"


namespace
{
Vector3 SCALE = Vector3(3.0f,1.0f,3.0f);
 float  SPEED = 300.0f;
 float LIMITED = 400.0f;
 Vector3 COLLISION_HEIGHT = Vector3(0.0f, 50.0f, 0.0f);
 Vector3 COLLISION_SIZE = Vector3(365.0f, 5.0f, 225.0f);
}

MovingFloor::MovingFloor()
{
	
}

MovingFloor::~MovingFloor()
{

}

bool MovingFloor::Start()
{
	m_movingmodelRender.Init("Assets/Texture/MovingFloor.tkm");
	m_movingmodelRender.SetScale(SCALE);
	//m_movingmodelRender.SetPosition(m_movePosition);
	m_movingmodelRender.Update();
	m_PhysicsStaticObject.CreateFromModel(m_movingmodelRender.GetModel(), m_movingmodelRender.GetModel().GetWorldMatrix());
	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");

	//コリジョンオブジェクトを動く床に設置する、
	//(キャラクターが上に乗ったら反応するようにしたいため).
	m_collisionObject->CreateBox(
		m_movePosition + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);
	m_collisionObject -> SetIsEnableAutoDelete(false);
	m_firstPosition = m_movePosition;

	m_player = FindGO<Player>("player");
	return true;
}


void MovingFloor::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}
	Vector3 oldPos = m_movePosition;
		Move();

		// 床がどれだけ動いたか計算
		Vector3 moveDelta = m_movePosition - oldPos;

		//静的物理オブジェクトの初期化
		m_PhysicsStaticObject.Release();
		m_PhysicsStaticObject.CreateFromModel
		(m_movingmodelRender.GetModel(),
			m_movingmodelRender.GetModel().GetWorldMatrix());
		m_movingmodelRender.Update();

		//m_PhysicsStaticObject.SetPosition(m_movePosition);
		m_collisionObject->SetPosition(m_movePosition + COLLISION_HEIGHT);

		if (m_collisionObject != nullptr && m_player != nullptr)
		{

			if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
			{
				//動く床の移動速度をキャラクターの移動速度に加算、
				m_player->AddPosition(moveDelta);
			}
		}
	
}


void MovingFloor::Move()
{
	Vector3 moveSpeed = Vector3::Zero;

	if (m_MovingFloorState == enMovingFloorState_MovingRight)
	{
		moveSpeed.z = -SPEED;
	}
	else if (m_MovingFloorState == enMovingFloorState_MovingLeft)
	{
		moveSpeed.z = SPEED;
	}

	m_movePosition += moveSpeed * g_gameTime->GetFrameDeltaTime();

	if (m_MovingFloorState == enMovingFloorState_MovingRight)
	{
		if (m_firstPosition.z - LIMITED >= m_movePosition.z)
		{
			m_MovingFloorState = enMovingFloorState_MovingLeft;
		}
	}
	else if (m_MovingFloorState == enMovingFloorState_MovingLeft)
	{
		if (m_firstPosition.z + LIMITED <= m_movePosition.z)
		{
			m_MovingFloorState = enMovingFloorState_MovingRight;
		}
	}
	m_movingmodelRender.SetPosition(m_movePosition);
	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが
	//衝突したら(キャラクターが動く床の上に乗ったら).
	//AddMoveSpeed(moveSpeed);
}


void MovingFloor::Render(RenderContext& rc)
{
	m_movingmodelRender.Draw(rc);
}

