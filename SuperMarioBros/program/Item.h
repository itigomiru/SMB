#pragma once
#include "Object.h"
#include "TileManager.h"
#include "SceneManager.h"
class Item : public Object
{
protected:
	Float2 spawnPos;
	TileManager* tileManager = nullptr;
	int spawnWait;
	bool SpawnUpdate();
	const float SPAWN_SPEED = 0.5f;
	const int SPAWN_WAIT_TIME = 12;
	const int OUT_OF_SCREEN_MASS = 3; // 画面外に出るまでのマス数
	virtual void CheckOutOfScreen(float cameraX) { if (pos.x < cameraX - (OUT_OF_SCREEN_MASS * TILE_SIZE))isDead = true; };

public:
	void virtual Update(float cameraX) = 0;
	void virtual Render(float cameraX) = 0;
	int itemType;
	int state;

	enum ITEM_STATE
	{
		IS_SPAWNING,
		IS_MOVING,
	};

	void SetTileManager(TileManager* tm);

};
