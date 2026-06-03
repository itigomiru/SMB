#pragma once
#include "Object.h"
#include "TileManager.h"
class Item : public Object
{
protected:
	Float2 spawnPos;
	TileManager* tileManager = nullptr;
	int spawnWait;
	bool SpawnUpdate();
	const float SPAWN_SPEED = 0.5f;
	const int SPAWN_WAIT_TIME = 12;
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
