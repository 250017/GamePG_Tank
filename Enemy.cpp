#include "Enemy.h"
#include "Engine/Model.h"
#include "Ground.h"


Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{
}

void Enemy::Initialize()
{
	timer = 0;
	mvPos_x = 0;
	mvPos_z = 0;
	hModel_ = Model::Load("Enemy.fbx");
	assert(hModel_ >= 0);//モデルの読み込みに失敗していないか	
}

void Enemy::Update()
{
	timer++;
	//例キャストして、浮いてたら、地面まで落とす
	RayCastData data;
	data.start = transform_.position_;
	data.start.y = 0.0f;//地面は
	data.dir = { 0, -1, 0 }; //真下にレイを飛ばす

	Ground* pGround = (Ground*)FindObject("Ground");//groundオブジェクトを探す

	int hGroundModel = pGround->GetModelHandle();//groundオブジェクトのモデルのハンドルを得る
	Model::RayCast(hGroundModel, &data);//

	if (data.hit == true)
	{
		transform_.position_.y = 0 - data.dist;
		//レイの発射位置から、地面までの距離を引く
	}
	
	if (timer % 180 == 0) {
		mvPos_x = rand() % 50 - 25;
		mvPos_z = rand() % 50 - 25;
	}
	transform_.position_.x += (mvPos_x - transform_.position_.x) / 180;
	transform_.position_.z += (mvPos_z - transform_.position_.z) / 180;





}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}
