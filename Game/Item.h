#pragma once
class Player;
class Item :public IGameObject
{
public:
	Item();
	~Item();
	//�X�V����
	void Update();
	//�`�揈��
	void Render(RenderContext& rc);
	//�ړ�����
	void Move();
	//��]����
	void Rotation();
	Player* m_player;//�v���C���[
	Vector3 m_itemposition;//���W
	Vector3 m_firstPosition;//�������W
private:
	ModelRender m_modelRender;//���f�������_�[
	Quaternion m_itemrot;//�N�H�[�^�j�I��
	

};

