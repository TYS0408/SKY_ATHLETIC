#include "stdafx.h"
#include "Game.h"
#include "Player.h"
#include "BackGround.h"
#include "GameCamera.h"
#include "StageObject01.h"
#include"ItemFloor.h"
#include "MovingFloor.h"
#include"MovingFloor2.h"
#include "Item.h"
#include "GameClear.h"
#include "nature/SkyCube.h"
#include "graphics/RenderingEngine.h"


Game::Game()
{
	g_soundEngine->ResistWaveFileBank(0, "Assets/SE/GameBGM.wav");
	//SoundSourceのオブジェクトを作成する。
	m_bgm = NewGO<SoundSource>(0);
	//WaveFileBankから登録されたwaveファイルのデータを持ってくる
	m_bgm->Init(0);
	//trueにすると、音がループする
	m_bgm->Play(true);
}

Game::~Game() 
{
	DeleteGO(m_player);
	DeleteGO(m_gameCamera);
	DeleteGO(m_backGround);
	DeleteGO(m_bgm);
	

	//forearch。
	//配列の最後まで走査する。
	//このコードを使うと名前が "movingfloor"の 
	//  MovingFloor 型オブジェクトを全て探して、ひとつずつ削除する
	auto movingFloorList = FindGOs<MovingFloor>("movingfloor");
	for (auto movingFloor : movingFloorList) 
	{
		DeleteGO(movingFloor);
	}

	auto movingFloor2List = FindGOs<MovingFloor2>("movingfloor");
	for (auto movingFloor2 : movingFloor2List)
	{
		DeleteGO(movingFloor2);
	}
	
	auto itemFloorList = FindGOs<ItemFloor>("itemfloor");
	for (auto itemFloor : itemFloorList)
	{
		DeleteGO(itemFloor);
	}

	auto ItemList = (FindGOs<Item>("Item"));
	for (auto Item : ItemList)
	{
		DeleteGO(Item);
	}	
}



bool Game::Start()
{
	
	InitSky();
	m_player = NewGO<Player>(0, "player");
	m_backGround = NewGO<BackGround>(0, "backGround");
	m_gameCamera = NewGO<GameCamera>(0, "gameCamera");
	m_stageObject01 = NewGO<StageObject01>(0, "stageObject");
	//ItemFloorの複数生成(Z方向)
	ItemFloor* Itemfloor1 = NewGO<ItemFloor>(0,"Itemfloor");
	Itemfloor1->m_ItemFloorPosition = { 0.0f, 2000.0f, 1400.0f };
	Itemfloor1->m_ItemFloorFirpos = Itemfloor1->m_ItemFloorPosition;

	//X方向のItemFloor
	ItemFloor* Itemfloor2 = NewGO<ItemFloor>(0, "Itemfloor");
	Itemfloor2->m_ItemFloorPosition = { 1500.0f,2000.0f,0.0f };
	Itemfloor2->m_ItemFloorFirpos = Itemfloor2->m_ItemFloorPosition;

    //-X方向のItemFloor
	ItemFloor* Itemfloor3 = NewGO<ItemFloor>(0, "Itemfloor");
	Itemfloor3->m_ItemFloorPosition = { -1500.0f,2000.0f,0.0f };
	//Itemfloor3->m_ItemFloorFirpos = Itemfloor3->m_ItemFloorPosition;
		

	m_movingFloor = NewGO<MovingFloor>(0, "movingfloor");
	m_movingFloor->  SetPosition(Vector3(0.0f, 2000.0f, 800.0f));

	MovingFloor2* movingfloor2 = NewGO<MovingFloor2>(0, "movingfloor");
	movingfloor2->m_movePosition2 = { 800.0f,2000.0f,0.0f };
	movingfloor2->m_firstPosition2 = movingfloor2->m_movePosition2;

	MovingFloor2* movingfloor3 = NewGO<MovingFloor2>(0, "movingfloor");
	movingfloor3->m_movePosition2 = { -800.0f,2000.0f,0.0f };
	movingfloor3->m_firstPosition2 = movingfloor3->m_movePosition2;
	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();
	//Itemの複数生成
	//塔の上
	Item* item1 = NewGO<Item>(0, "item");
	item1->m_itemposition = { 0.0f,2100.0f,0.0f };
	item1->m_firstPosition = item1->m_itemposition;
	//Z方向のItem
	Item* item2 = NewGO<Item>(0, "item");
	item2->m_itemposition = { 0.0f,2100.0f,1400.0f };
	item2->m_firstPosition = item2->m_itemposition;

	//X方向のItem
	Item* item3 = NewGO<Item>(0,"item");
	item3->m_itemposition = { 1500.0f,2100.0f,0.0f };
	item3->m_firstPosition = item3->m_itemposition;

	//-X方向のItem

	Item* item4 = NewGO<Item>(0, "item");
	item4->m_itemposition = { -1500.0f,2100.0f,0.0f };
	item4->m_firstPosition = item4->m_itemposition;

	m_gameCamera->SetTarget(m_player);
	return true;

}

void Game::InitSky()
{
	//現在のスカイキューブを削除
	DeleteGO(m_skycube);
	m_skycube = NewGO<SkyCube>(0, "skycube");
	m_skycube->SetLuminance(1.0f);//明るさ設定
	m_skycube->SetType((EnSkyCubeType)m_skyCubeType);//スカイキューブのタイプ設定
	g_renderingEngine->SetAmbientByIBLTexture(m_skycube->GetTextureFilePath(), 1.0f);
	//環境光の計算のためのIBLテクスチャをセット
	g_renderingEngine->SetDirectionLight(0, g_vec3Zero, g_vec3Zero);
}

void Game::Text()
{
	m_elapsedTime += g_gameTime->GetFrameDeltaTime();
	//残りアイテム数のテキスト
	int collectItem = 4 - m_player->m_ItemCount;
	wchar_t text[256];
	swprintf_s(text, 256, L"残りのItemの数:%d", collectItem);
	m_fontRender.SetText(text);
	m_fontRender.SetPosition({ -800.0f,100.0f,0.0f });//フォントポジション
	m_fontRender.SetColor(g_vec4Yellow);//フォントカラー

	//経過時間のテキスト
	int minitu = (int)m_elapsedTime  /60;
	int seconds = (int)m_elapsedTime % 60;
	
	//経過時間
	wchar_t timerText[256];
	swprintf_s(timerText, 256, L"経過時間:%02d:%02d",minitu,seconds, m_elapsedTime);
	//文字のセット
	m_timerFontRender.SetText(timerText);
	//文字のポジション
	m_timerFontRender.SetPosition({ -250.0f,540.0f,0.0f });
	//文字の大きさ
	m_timerFontRender.SetScale(1.5f);
	//文字の色
	m_timerFontRender.SetColor(g_vec4White);




}

void Game::Update()
{

	//ItemCountが4になったら
	if (m_player->m_ItemCount == 4)
	{
		
	  GameClear* gameclear = NewGO<GameClear>(0, "GameClear");
	  gameclear->SetClearTime(m_elapsedTime);
		DeleteGO(this);
		return;
	}
	Text();

	////空を変更
	//if (g_pad[0]->IsTrigger(enButtonRight))
	//{
	//	m_skyCubeType++;
	//	m_skyCubeType = m_skyCubeType % enSkyCubeType_Num;
	//	InitSky();
	//}
	//if (g_pad[0]->IsTrigger(enButtonLeft))
	//{
	//	m_skyCubeType--;
	//	if (m_skyCubeType < 0)
	//	{
	//		m_skyCubeType = enSkyCubeType_Num - 1;
	//	}
	//	InitSky();
	//}
}

void Game::Render(RenderContext& rc)
{
	m_fontRender.Draw(rc);
	m_timerFontRender.Draw(rc);
}

