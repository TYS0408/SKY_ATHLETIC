#pragma once
class BackGround : public IGameObject
{
public:
	BackGround();
	~BackGround();


	//void Update();
	//•`‰æŠÖ”
	void Render(RenderContext& rc);


	//ƒ‚ƒfƒ‹ƒŒƒ“ƒ_[
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;
};

