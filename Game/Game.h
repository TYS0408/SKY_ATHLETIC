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
	//�c��A�C�e�����̌v�Z
	//int CollectItem = 4 - m_player->m_ItemCount;
	FontRender m_fontRender;
	FontRender m_timerFontRender;
	float m_elapsedTime = 0.0f;//�o�ߎ���
	SoundSource* m_bgm;
	
private:
	ModelRender m_modelRender;
	Vector3 m_pos;
	BackGround* m_backGround;//�w�i
	Player* m_player;//�v���C���[
	GameCamera* m_gameCamera;//�J����
	SkyCube* m_skycube;//�X�J�C�L���[�u
	int m_skyCubeType = enSkyCubeType_Day;
	StageObject01* m_stageObject01;//���̃I�u�W�F�N�g
	MovingFloor* m_movingFloor;//������x
	MovingFloor2* m_movingFloor2;//������z
	Item* m_item;
	ItemFloor* m_ItemFloor;
	
};

