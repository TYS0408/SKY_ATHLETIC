#pragma once
class StageObject01: public IGameObject
{
public:
	StageObject01();
	~StageObject01();

	//�`��֐�
	void Render(RenderContext& rc);

	//���f�������_�[
	ModelRender m_modelRender;
	PhysicsStaticObject physicsStaticObject;//�����蔻��

};

