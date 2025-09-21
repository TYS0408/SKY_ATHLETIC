#pragma once
#include "sound/SoundSource.h"
class GameTitle :public IGameObject
{
public:
	GameTitle();
	~GameTitle();
	//描画関数
	void Render(RenderContext& rc);
	//更新処理
	void Update();
	//スプライトレンダー
	SpriteRender m_spriteRender;
	SoundSource* m_titleBGM;
};

