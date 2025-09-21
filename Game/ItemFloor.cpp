#include "stdafx.h"
#include "ItemFloor.h"
ItemFloor::ItemFloor()
{
	m_modelRender.Init("Assets/Texture/ItemFloor.tkm");
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix());
	//�����蔻�����������
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	
	
}

ItemFloor::~ItemFloor()
{

}

void ItemFloor::Move()
{
	m_physicsStaticObject.Release();

	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());

	m_modelRender.SetPosition(m_ItemFloorPosition);
}

void ItemFloor::Update()
{
	Move();

	//�X�V����
	m_modelRender.Update();
	
}

void ItemFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
