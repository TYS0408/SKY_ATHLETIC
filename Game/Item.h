#pragma once
class Player;
class Item :public IGameObject
{
public:
	Item();
	~Item();
	//更新処理
	void Update();
	//描画処理
	void Render(RenderContext& rc);
	//移動処理
	void Move();
	//回転処理
	void Rotation();
	Player* m_player;//プレイヤー
	Vector3 m_itemposition;//座標
	Vector3 m_firstPosition;//初期座標
private:
	ModelRender m_modelRender;//モデルレンダー
	Quaternion m_itemrot;//クォータニオン
	

};

