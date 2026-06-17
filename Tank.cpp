#include "Tank.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Ground.h"
#include "Engine/Camera.h"

namespace
{
	const XMVECTOR vFront = { 0, 0, 1, 0 };//タンク前のベクトル
	const float moveSpeed = 0.1f;//タンクの移動速度
	const float CAM_HEIGHT_BIAS = 0.2f;//カメラの高さの調整値
	enum CAM_TYPE
	{
		FIXED_CAM, //固定カメラ
		TPS_CAM, //三人称視点カメラ
		TPS_CAMROT, //三人称視点カメラ
		FPS_CAM, //一人称カメラ
		CAM_TYPE_MAX
	};
	
}

Tank::Tank(GameObject* parent)
	:GameObject(parent, "Tank"), hModel_(-1), camType_(FIXED_CAM)
{
}

Tank::~Tank()
{
}

void Tank::Initialize()
{
	hModel_ = Model::Load("TankBody.fbx");
	assert(hModel_ >= 0);//モデルの読み込みに失敗していないか確認
}

void Tank::Update()
{
	XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//ロード：書き込み
	XMMATRIX matRot = XMMatrixRotationY(XMConvertToRadians(transform_.rotate_.y));//Y軸回転行列を作る

	XMVECTOR vMove = XMVector3TransformCoord(vFront, matRot);
	if (Input::IsKeyDown(DIK_C)) {
		camType_ = (camType_ + 1) % CAM_TYPE_MAX;
	}
	switch (camType_)
	{
	case FIXED_CAM:
		//固定カメラの処理
		SetFixedCam();
		break;
	case TPS_CAM:
	{
		//三人称カメラの処理
		XMFLOAT3 camPos = transform_.position_;//タンクの位置をカメラの位置にする
		camPos.y = camPos.y + 5.0f;//カメラの高さをタンクの位置より少し高くする
		camPos.z = camPos.z - 13.0f;//カメラの位置をタンクの位置より少し後ろにする
		Camera::SetPosition(camPos);//カメラの位置を設定
		Camera::SetTarget(transform_.position_);//カメラの注視点をタンクの位置にする
	}
		break;

	case TPS_CAMROT:
	{
		//三人称視点カメラ（回転）の処理
		XMFLOAT3 camPos; //タンクの位置をカメラの位置にする
		XMVECTOR vCAM = { 0.0f, 3.0f, -7.0f, 0.0f };//カメラの位置をタンクの位置より少し後ろにする
		vCAM = XMVector3TransformCoord(vCAM, matRot);//カメラの注視点をタンクの位置にする
		XMStoreFloat3(&camPos, vPos + vCAM); //カメラの位置をタンクの位置に反映させる
		Camera::SetPosition(camPos);//カメラの位置を設定
		Camera::SetTarget(transform_.position_);//カメラの注視点をタンクの位置にする
	}
		break;
	case FPS_CAM:
		//一人称カメラの処理
		XMFLOAT3 camPos = transform_.position_;//タンクの位置をカメラの位置にする
		camPos.y = camPos.y + CAM_HEIGHT_BIAS;
		Camera::SetPosition(camPos);//カメラの位置をタンクの位置にする
		XMFLOAT3 camTarget;
		XMStoreFloat3(&camTarget, vPos + vMove);//カメラの注視点をタンクの前方にする
		Camera::SetTarget(camTarget);
		break;
	}
	
	if (Input::IsKey(DIK_A)) //左に回転する
	{
		transform_.rotate_.y -= 1;
	}
	if (Input::IsKey(DIK_D))//右に回転する
	{
		transform_.rotate_.y += 1;
	}
	Debug::Log("Yangle = %d", camType_);
	Debug::Log(transform_.rotate_.y, true); //後のtrueは改行するかどうか
	//wキーを押している間前に進む
	if (Input::IsKey(DIK_W)) //前に進む
	{
		vPos = vPos + moveSpeed * vMove;
		XMStoreFloat3(&transform_.position_, vPos);//ストア：書き込み

	}

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

	
}

void Tank::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Tank::Release()
{
}

void Tank::SetFixedCam()
{
	Camera::SetTarget(XMFLOAT3(0, 0, 0));
	Camera::SetPosition(XMFLOAT3(0, 20, -30));
}
