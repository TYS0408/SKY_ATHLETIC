#include "stdafx.h"
#include "GameTitle.h"
#include "Game.h"
#include"sound/SoundEngine.h"
GameTitle::GameTitle()
{
	//画像を読み込む
	m_spriteRender.Init("Assets/Image/GameTitle.dds", 1920, 1080.0f);

	//タイトルのBGMを読み込む。

	g_soundEngine->ResistWaveFileBank(0, "Assets/BGM・SE/GameTitleBGM.wav");



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
//画像を描画
	m_spriteRender.Draw(rc);
}
