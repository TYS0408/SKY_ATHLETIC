#pragma once

#include "Level3DRender/LevelRender.h"

class Player;
class BackGround;
class Player;
class GameCamera;
class StageObject01;
class ItemFloor;
class MovingFloor;
class MovingFloor2;
class Item;
class Game : public IGameObject
{
public:
	Game() ;
	~Game() ;
	bool Start()override;
	bool m_isFinished;
	void Update();
	void InitSky();
	void Text();
	void Render(RenderContext& rc);
	//残りアイテム数の計算
	//int CollectItem = 4 - m_player->m_ItemCount;
	FontRender m_fontRender;
	FontRender m_timerFontRender;
	float m_elapsedTime = 0.0f;//経過時間
	SoundSource* m_bgm;
	
private:
	ModelRender m_modelRender;
	Vector3 m_pos;
	BackGround* m_backGround;//背景
	Player* m_player;//プレイヤー
	GameCamera* m_gameCamera;//カメラ
	SkyCube* m_skycube;//スカイキューブ
	int m_skyCubeType = enSkyCubeType_Day;
	StageObject01* m_stageObject01;//塔のオブジェクト
	MovingFloor* m_movingFloor;//動く床x
	MovingFloor2* m_movingFloor2;//動く床z
	Item* m_item;
	ItemFloor* m_ItemFloor;
	
};

