#include "stdafx.h"
#include "GameTitle.h"
#include "Game.h"
#include"sound/SoundEngine.h"
GameTitle::GameTitle()
{
	//�摜��ǂݍ���
	m_spriteRender.Init("Assets/Image/GameTitle.dds", 1920, 1080.0f);

	//�^�C�g����BGM��ǂݍ��ށB

	g_soundEngine->ResistWaveFileBank(0, "Assets/BGM�ESE/GameTitleBGM.wav");



}

GameTitle::~GameTitle()
{
	DeleteGO(m_titleBGM);
}

void GameTitle::Update()
{
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		NewGO<Game>(0);
		DeleteGO(this);
	}
}

void GameTitle::Render(RenderContext& rc)
{
//�摜��`��
	m_spriteRender.Draw(rc);
}
