#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "Enemy.h"
//#include "TankHead.h"

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

void PlayScene::Initialize()
{
	Instantiate<Ground>(this);
	Instantiate<Tank>(this);
	Instantiate<Enemy>(this);
	//Instantiate<TankHead>(this);
}

void PlayScene::Update()
{
}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{
}
