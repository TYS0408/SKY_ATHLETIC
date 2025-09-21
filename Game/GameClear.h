#pragma once
class GameClear : public IGameObject
{

public:
	GameClear();
	~GameClear();
	void SetClearTime(float time)
	{
		m_clearTime = time;
		
	}
	bool Start();
	void Update();
	void Render(RenderContext& rc);
	

private:
	SpriteRender m_spriteRender;
	FontRender m_timerFont;

	float m_clearTime = 0.0f;
	float m_elapsedTime = 0.0f;//Œo‰ßŽžŠÔ
	
};

