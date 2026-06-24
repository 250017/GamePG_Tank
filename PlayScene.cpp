#include "PlayScene.h"
#include "Ground.h"
#include "Tank.h"
#include "Enemy.h"
//#include "TankHead.h"
#include <vector>

PlayScene::PlayScene(GameObject* parent)
	:GameObject(parent, "PlayScene")
{
}

void PlayScene::Initialize()
{
	timer_ = 0;

	Instantiate<Ground>(this);
	Instantiate<Tank>(this);

	std::vector<Enemy*> enemies;
	for (int i = 0; i < 5; i++) {
	enemies.push_back(Instantiate<Enemy>(this));
}
	
	
	//Instantiate<TankHead>(this);
}

void PlayScene::Update()
{
	timer_++;
	std::vector<Enemy*> enemies;
	if (timer_ % 120 == 0) enemies.push_back(Instantiate<Enemy>(this));
}

void PlayScene::Draw()
{

}

void PlayScene::Release()
{
}
