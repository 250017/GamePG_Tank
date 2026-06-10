#include "Ground.h"
#include "Engine/Model.h"

Ground::Ground(GameObject* parent)
	:GameObject(parent, "Ground"), hModel_(-1)
{
}



Ground::~Ground()
{
}//デストラクタ（オブジェクトが削除されるときに呼ばれる関数）

void Ground::Initialize()
{
	//モデルの読み込み
	hModel_ = Model::Load("Ground.fbx");
	assert(hModel_ >= 0);//モデルの読み込みに失敗していないか確認
}

void Ground::Update()
{
}

void Ground::Draw()
{
	Model::SetAnimFrame;
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Ground::Release()
{
}
