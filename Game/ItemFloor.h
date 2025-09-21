#pragma once
class ItemFloor : public IGameObject
{
public:
	ItemFloor();
	~ItemFloor();
	

	void Update();
	void Move();
	//ï`âÊä÷êî
	void Render(RenderContext& rc);
	Vector3 m_ItemFloorPosition;
	Vector3 m_ItemFloorFirpos;
	ModelRender m_modelRender;
	PhysicsStaticObject m_physicsStaticObject;

};

