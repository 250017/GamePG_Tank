#include "Bullet.h"
#include "Engine/Model.h"
#include "Engine//Input.h"

Bullet::Bullet(GameObject* parent)
	:GameObject(parent, "Bullet"), hModel_(-1), move_(XMFLOAT3(0, 1, 0))
{
	//コンストラクタはメンバの初期化をする場所
}

void Bullet::Initialize()
{
	hModel_ = Model::Load("Bullet.fbx");
	assert(hModel_ >= 0);//モデルの読み込みに失敗していないか
	timer = 0;
}

void Bullet::Update()
{
	timer++;
	//transform_.position_ = transform_.position_ + move_;//弾の進行方向に移動する
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//ロード：読み込み
	XMVECTOR vMove = XMLoadFloat3(&move_);//ロード：読み込み
	vPos = vPos + vMove;//弾の進行方向に移動する
	XMStoreFloat3(&transform_.position_, vPos);//ストア：書き込み

	if (transform_.position_.z > 50.0f || transform_.position_.z < -50.0f 
		|| transform_.position_.x > 50.0f || transform_.position_.x < -50.0f)
	{
		KillMe();//弾がある程度遠くに行ったら消す
	}

	move_.y -= 0.0025f;





}

void Bullet::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Bullet::Release()
{
}
