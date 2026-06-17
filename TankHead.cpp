#include "TankHead.h"
#include "Engine/Input.h"
#include "Engine/Model.h"
#include "Engine/Debug.h"
#include "Tank.h"

namespace
{
}

TankHead::TankHead(GameObject* parent)
	:GameObject(parent, "Tank"), hModel_(-1)
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
	const XMVECTOR vPos = XMLoadFloat3(&transform_.position_);//ロード：書き込み

}

void TankHead::Draw()
{
	Tank* pTank = (Tank*)FindObject("Tank");//Tankオブジェクトを探す
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void TankHead::Release()
{
}
