#include "stdafx.h"
#include "StageObject01.h"

StageObject01::StageObject01()
{
	m_modelRender.Init("Assets/Texture/StageObject01.tkm");
	physicsStaticObject.CreateFromModel(m_modelRender.GetModel(),
		m_modelRender.GetModel().GetWorldMatrix());
	//“–‚½‚è”»’è‚ð‰ÂŽ‹‰»‚·‚é
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
}

StageObject01::~StageObject01()
{

}


void StageObject01::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}
