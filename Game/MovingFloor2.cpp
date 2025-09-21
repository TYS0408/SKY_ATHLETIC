#include "stdafx.h"
#include "MovingFloor2.h"
#include"Player.h"

namespace
{
	Vector3 SCALE = Vector3(3.0f, 1.0f, 3.0f);
	float  SPEED = 300.0f;
	float LIMITED = 400.0f;
	Vector3 COLLISION_HEIGHT = Vector3(0.0f, 50.0f, 0.0f);
	Vector3 COLLISION_SIZE = Vector3(365.0f, 5.0f, 225.0f);
}

MovingFloor2::MovingFloor2()
{

}

MovingFloor2::~MovingFloor2()
{

}

bool MovingFloor2::Start()
{
	m_movingmodelRender.Init("Assets/Texture/MovingFloor2.tkm");
	m_movingmodelRender.SetScale(SCALE);
	//m_movingmodelRender.SetPosition(m_movePosition);
	m_movingmodelRender.Update();
	m_PhysicsStaticObject.CreateFromModel(m_movingmodelRender.GetModel(), m_movingmodelRender.GetModel().GetWorldMatrix());
	m_collisionObject = NewGO<CollisionObject>(0, "collisionObject");

	//コリジョンオブジェクトを動く床に設置する、
	//(キャラクターが上に乗ったら反応するようにしたいため).
	m_collisionObject->CreateBox(
		m_movePosition2 + COLLISION_HEIGHT,
		Quaternion::Identity,
		COLLISION_SIZE
	);
	m_collisionObject->SetIsEnableAutoDelete(false);
	m_firstPosition2 = m_movePosition2;

	m_player = FindGO<Player>("player");
	return true;
}


void MovingFloor2::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}
	

	Vector3 oldPos = m_movePosition2;
	Move();

	Vector3 moveDelta = m_movePosition2 - oldPos;

	if (m_collisionObject->IsHit(m_player->GetCharacterController()) == true)
	{
		//動く床の移動速度をキャラクターの移動速度に加算、
		m_player->AddPosition(moveDelta);
	}
	//静的物理オブジェクトの初期化
	m_PhysicsStaticObject.Release();
	m_PhysicsStaticObject.CreateFromModel
	(m_movingmodelRender.GetModel(),
		m_movingmodelRender.GetModel().GetWorldMatrix());
	m_movingmodelRender.Update();

	//m_PhysicsStaticObject.SetPosition(m_movePosition);
	m_collisionObject->SetPosition(m_movePosition2 + COLLISION_HEIGHT);

}


void MovingFloor2::Move()
{
	Vector3 moveSpeed = Vector3::Zero;

	if (m_MovingFloorState == enMovingFloorState_MovingRight)
	{
		moveSpeed.x = -SPEED;
	}
	else if (m_MovingFloorState == enMovingFloorState_MovingLeft)
	{
		moveSpeed.x = SPEED;
	}

	m_movePosition2 += moveSpeed * g_gameTime->GetFrameDeltaTime();

	if (m_MovingFloorState == enMovingFloorState_MovingRight)
	{
		if (m_firstPosition2.x - LIMITED >= m_movePosition2.x)
		{
			m_MovingFloorState = enMovingFloorState_MovingLeft;
		}
	}
	else if (m_MovingFloorState == enMovingFloorState_MovingLeft)
	{
		if (m_firstPosition2.x + LIMITED <= m_movePosition2.x)
		{
			m_MovingFloorState = enMovingFloorState_MovingRight;
		}
	}
	m_movingmodelRender.SetPosition(m_movePosition2);
	//コリジョンオブジェクトとプレイヤーのキャラクターコントローラーが
	//衝突したら(キャラクターが動く床の上に乗ったら).
	

}
void MovingFloor2::Render(RenderContext& rc)
{
	m_movingmodelRender.Draw(rc);
}
