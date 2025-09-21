#include "stdafx.h"
#include "GameClear.h"
#include"GameTitle.h"


GameClear::GameClear()
{
	//ゲームクリア画面を読み込む
	m_spriteRender.Init("Assets/Image/GameClear.dds", 1920.0f, 1080.0f);
}

GameClear::~GameClear()
{
	
}

bool GameClear::Start()
{

	
	return true;
}




void GameClear::Update()
{

	int minitu = static_cast<int>(m_clearTime) / 60;
	int seconds = static_cast<int>(m_clearTime) % 60;
	m_elapsedTime += g_gameTime->GetFrameDeltaTime();
	//経過時間
	wchar_t timerText[256];
	swprintf_s(timerText, 256, L"クリアタイム:%02d:%02d", minitu, seconds, m_elapsedTime);
	//文字のセット
	m_timerFont.SetText(timerText);
	//文字のポジション
	m_timerFont.SetPosition({ -320.0f,-300.0f,0.0f });
	//文字の大きさ
	m_timerFont.SetScale(1.5f);
	//文字の色
	m_timerFont.SetColor(g_vec4White);
	
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//タイトルのオブジェクト生成
		NewGO<GameTitle>(0, "gametitle");
		//自信を削除
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_timerFont.Draw(rc);
}
