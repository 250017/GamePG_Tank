#pragma once
#include "Engine//GameObject.h"

class TankHead :
    public GameObject
{
public:
	//コンストラクタ
	//引数：parent  親オブジェクト（SceneManager）
	TankHead(GameObject* parent);
	//デストラクタ
	~TankHead();

	//初期化
	void Initialize() override;

	//更新
	void Update() override;

	//描画
	void Draw() override;

	//開放
	void Release() override;

	//着弾点計算
	void GetCirclePos();
private:
	int hModel_;//タンクヘッドモデルのハンドル
	int hModel_Circle_;//弾の着弾地点
};

