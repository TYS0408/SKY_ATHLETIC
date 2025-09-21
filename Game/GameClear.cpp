#include "stdafx.h"
#include "GameClear.h"
#include"GameTitle.h"


GameClear::GameClear()
{
	//�Q�[���N���A��ʂ�ǂݍ���
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
	//�o�ߎ���
	wchar_t timerText[256];
	swprintf_s(timerText, 256, L"�N���A�^�C��:%02d:%02d", minitu, seconds, m_elapsedTime);
	//�����̃Z�b�g
	m_timerFont.SetText(timerText);
	//�����̃|�W�V����
	m_timerFont.SetPosition({ -320.0f,-300.0f,0.0f });
	//�����̑傫��
	m_timerFont.SetScale(1.5f);
	//�����̐F
	m_timerFont.SetColor(g_vec4White);
	
	if (g_pad[0]->IsTrigger(enButtonA))
	{
		//�^�C�g���̃I�u�W�F�N�g����
		NewGO<GameTitle>(0, "gametitle");
		//���M���폜
		DeleteGO(this);
	}
}

void GameClear::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_timerFont.Draw(rc);
}
