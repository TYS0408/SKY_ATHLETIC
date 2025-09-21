#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include"sound/SoundEngine.h"
#include"sound/SoundSource.h"

Item::Item()
{
	m_modelRender.Init("Assets/Texture/Item_Card.tkm");

	m_player = FindGO<Player>("player");
	g_soundEngine->ResistWaveFileBank(1, "Assets/BGM�ESE/ItemSE.wav");
}

Item::~Item()
{

}

void Item::Move()
{
	//�G�`������ɍ��W��������
	m_modelRender.SetPosition(m_itemposition);
}

void Item::Rotation()
{
	m_itemrot.AddRotationDegY(3.0f);
	


	m_modelRender.SetRotation(m_itemrot);
}
void Item::Update()
{

    //�ړ�����
	Move();
	
	//��]����
	Rotation();
	

	//�v���C���[����item�Ɍ������x�N�g�����v�Z
	Vector3 diff = m_player->m_position - m_itemposition;
	//�x�N�g���̒�����120.0f��菬����������B
	if (diff.Length() <= 100.0f)
	{
		//�J�E���g�𑝂₷
		m_player->m_ItemCount += 1;

		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		//���ʉ��̓��[�v�����Ȃ��̂�false�ɂ���
		se->Play(false);
		//���ʂ��グ��
		se->SetVolume(3.5f);
		//item�ɐG���ƍ폜
		DeleteGO(this);
	}
	//�G�`������̍X�V����
	m_modelRender.Update();
}



void Item::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

