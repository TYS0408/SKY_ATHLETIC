#pragma once
class StageObject01: public IGameObject
{
public:
	StageObject01();
	~StageObject01();

	//•`‰æŠÖ”
	void Render(RenderContext& rc);

	//ƒ‚ƒfƒ‹ƒŒƒ“ƒ_[
	ModelRender m_modelRender;
	PhysicsStaticObject physicsStaticObject;//“–‚½‚è”»’è

};

