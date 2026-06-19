#pragma once
#include "Engine/GameObject.h"
class Enemy :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	Enemy(GameObject* parent);
	//デストラクタ
	~Enemy() {};//インライン定義

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;
	void SetMoveVector(XMFLOAT3 move) { move_ = move; }//弾の進行方向をセットする関数
private:
	int hModel_;//弾モデルのハンドル
	XMFLOAT3 move_;//弾の進行方向
	int timer;
	int mvPos_x;
	int mvPos_z;
};





