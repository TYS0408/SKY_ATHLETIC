#pragma once
#include "sound/SoundSource.h"
class GameTitle :public IGameObject
{
public:
	GameTitle();
	~GameTitle();
	//�`��֐�
	void Render(RenderContext& rc);
	//�X�V����
	void Update();
	//�X�v���C�g�����_�[
	SpriteRender m_spriteRender;
	SoundSource* m_titleBGM;
};

