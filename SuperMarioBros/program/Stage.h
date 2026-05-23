#pragma once
#include "Scene.h"
#include "ObjectManager.h"
#include "TileManager.h"
#include "EnemySpawner.h"
#include "Player.h"

class Stage : public Scene
{
private :
	//	ステージに必要な変数を宣言
	ObjectManager objectManager;
	TileManager tileManager;
	EnemySpawner enemySpawner;
	Player* player = nullptr;
public:
	void Init() override;
	void Update() override;
	void Render() override;
	~Stage() override;


	float cameraX = 0.0f;
};
