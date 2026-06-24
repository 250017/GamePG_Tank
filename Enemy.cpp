#include "Enemy.h"
#include "Engine/Model.h"
#include "Ground.h"
#include "Engine/SphereCollider.h"


Enemy::Enemy(GameObject* parent)
	:GameObject(parent, "Enemy"), hModel_(-1)
{
}

void Enemy::Initialize()
{
	timer = 0;
	float firstPos_x = ((float)rand() / RAND_MAX) * 20.0f - 10.0f;
	float firstPos_z = ((float)rand() / RAND_MAX) * 20.0f - 10.0f;
	
	transform_.position_.x = firstPos_x;
	transform_.position_.z = firstPos_z;
	newPos_x = firstPos_x;
	newPos_z = firstPos_z;
	hModel_ = Model::Load("Enemy.fbx");
						//ハンドル、開始フレーム、アニメーション速度
	Model::SetAnimFrame(hModel_, 1, 100, 1.0f);
	assert(hModel_ >= 0);//モデルの読み込みに失敗していないか	
	SphereCollider* collider = new SphereCollider({ 0, 0, 0 }, 0.5);
	AddCollider(collider);

	

	mvs_ = 0.05; //動く速さ

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
	
	if (timer % 180 < 1) {
		newPos_x = rand() % 40 - 20;
		newPos_z = rand() % 40 - 20;
	}
	float mvP_x = newPos_x - transform_.position_.x;//移動量
	float mvP_z = newPos_z - transform_.position_.z;
	if (mvP_x > 0 && newPos_x > transform_.position_.x)
		transform_.position_.x += mvs_;
	if (mvP_x < 0 && newPos_x < transform_.position_.x)
		transform_.position_.x -= mvs_;
	if (mvP_z > 0 && newPos_z > transform_.position_.z)
		transform_.position_.z += mvs_;
	if (mvP_z < 0 && newPos_z < transform_.position_.z)
		transform_.position_.z -= mvs_;



}

void Enemy::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Enemy::Release()
{
}
