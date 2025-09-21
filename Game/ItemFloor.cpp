#include "stdafx.h"
#include "ItemFloor.h"
ItemFloor::ItemFloor()
{
	m_modelRender.Init("Assets/Texture/ItemFloor.tkm");
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix());
	//ìñÇΩÇËîªíËÇâ¬éãâªÇ∑ÇÈ
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

	//çXêVèàóù
	m_modelRender.Update();
	
}

void ItemFloor::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
