#include "TankHead.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Tank.h"
#include "Bullet.h"

namespace
{
}

TankHead::TankHead(GameObject* parent)
	:GameObject(parent, "TankHead"), hModel_(-1)
{
	
}

TankHead::~TankHead()
{
}

void TankHead::Initialize()
{
	hModel_ = Model::Load("TankHead.fbx");
	assert(hModel_ >= 0);//モデルの読み込みに失敗していないか	
}

void TankHead::Update()
{
	if (Input::IsKey(DIK_LEFT))
	{
		transform_.rotate_.y -= 1;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		transform_.rotate_.y += 1;
	}
	if (Input::IsKeyDown(DIK_SPACE))
	{
		XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");//タンクヘッド
		XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");

		XMVECTOR vTop = XMLoadFloat3(&cannonTop);
		XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);

		XMVECTOR vMove = XMVectorSubtract(vTop, vRoot);
		//XMVECTOR vMove = vTop - vRoot;//法大の向きのベクトルを作る
		vMove = 0.2f * vMove;//弾のスピードを設定
		XMFLOAT3 move;
		XMStoreFloat3(&move, vMove);//XMFLOAT3に戻す
		

		//弾を生成する
		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());//親の親にして弾を出す
		pBullet->SetMoveVector(move);
		pBullet->SetPosition(cannonTop);
	}
}

void TankHead::Draw()
{
	
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
