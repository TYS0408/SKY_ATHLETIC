#include "stdafx.h"
#include "BackGround.h"

BackGround::BackGround()
{
	m_modelRender.Init("Assets/Texture/GlassStage02.tkm");
	m_modelRender.Update();
	m_physicsStaticObject.CreateFromModel(m_modelRender.GetModel(), m_modelRender.GetModel().GetWorldMatrix());
	//�����蔻��`��
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();


}

BackGround::~BackGround()
{

}



void BackGround::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
