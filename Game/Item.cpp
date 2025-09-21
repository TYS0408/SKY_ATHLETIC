#include "stdafx.h"
#include "Item.h"
#include "Player.h"
#include"sound/SoundEngine.h"
#include"sound/SoundSource.h"

Item::Item()
{
	m_modelRender.Init("Assets/Texture/Item_Card.tkm");

	m_player = FindGO<Player>("player");
	g_soundEngine->ResistWaveFileBank(1, "Assets/BGM・SE/ItemSE.wav");
}

Item::~Item()
{

}

void Item::Move()
{
	//絵描きさんに座標を教える
	m_modelRender.SetPosition(m_itemposition);
}

void Item::Rotation()
{
	m_itemrot.AddRotationDegY(3.0f);
	


	m_modelRender.SetRotation(m_itemrot);
}
void Item::Update()
{

    //移動処理
	Move();
	
	//回転処理
	Rotation();
	

	//プレイヤーからitemに向かうベクトルを計算
	Vector3 diff = m_player->m_position - m_itemposition;
	//ベクトルの長さが120.0fより小さかったら。
	if (diff.Length() <= 100.0f)
	{
		//カウントを増やす
		m_player->m_ItemCount += 1;

		SoundSource* se = NewGO<SoundSource>(0);
		se->Init(1);
		//効果音はループさせないのでfalseにする
		se->Play(false);
		//音量を上げる
		se->SetVolume(3.5f);
		//itemに触れると削除
		DeleteGO(this);
	}
	//絵描きさんの更新処理
	m_modelRender.Update();
}



void Item::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}

