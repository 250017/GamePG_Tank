#include "TankHead.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Tank.h"
#include "Bullet.h"

namespace
{
	Transform circletransform;

	XMFLOAT3 move;//XMFLOAT3に戻す用

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
	hModel_Circle_ = Model::Load("Circle.fbx");
	assert(hModel_Circle_ >= 0);

	circletransform.position_ = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
	circletransform.rotate_ = XMFLOAT3{ 0.0f, 0.0f, 0.0f };
	circletransform.scale_ = XMFLOAT3{ 1.0f, 1.0f, 1.0f };
}

void TankHead::Update()
{
	XMFLOAT3 cannonTop = Model::GetBonePosition(hModel_, "Top");//タンクヘッド
	XMFLOAT3 cannonRoot = Model::GetBonePosition(hModel_, "Root");

	XMVECTOR vTop = XMLoadFloat3(&cannonTop);
	XMVECTOR vRoot = XMLoadFloat3(&cannonRoot);

	XMVECTOR vMove = XMVectorSubtract(vTop, vRoot);
	//XMVECTOR vMove = vTop - vRoot;//法大の向きのベクトルを作る
	vMove = 0.2f * vMove;//弾のスピードを設定
	XMStoreFloat3(&move, vMove);//XMFLOAT3に戻す
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
		//弾を生成する
		Bullet* pBullet = Instantiate<Bullet>(GetParent()->GetParent());//親の親にして弾を出す
		pBullet->SetMoveVector(move);
		pBullet->SetPosition(cannonTop);

		
	}

	//弾の着弾点計算

		// 着弾予測位置計算用
	XMFLOAT3 predictPosition = cannonTop;

	// 発射直後の速度を予測用にコピーする
	XMFLOAT3 predictMove = move;


	// 最大300フレーム先まで弾道を予測する
	for (int frame = 0; frame < 300; frame++)
	{
		// Bulletと同じ重力をY方向速度に加える
		predictMove.y -= 0.0025f;

		// 現在の速度を予測位置に加える
		predictPosition.x += predictMove.x;
		predictPosition.y += predictMove.y;
		predictPosition.z += predictMove.z;

		// 地面まで落下したら、それ以上の計算を終了する
		if (predictPosition.y <= -2.0f)
		{
			// 地面の高さに合わせる
			predictPosition.y = 0.0f;

			// 繰り返しを終了する
			break;
		}
	}
	// 計算した着弾地点に円形マーカーを配置する
	circletransform.position_ = predictPosition;
}

void TankHead::Draw()
{
	
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);

	Model::SetTransform(hModel_Circle_, circletransform);
	Model::Draw(hModel_Circle_);
}

void TankHead::Release()
{
}