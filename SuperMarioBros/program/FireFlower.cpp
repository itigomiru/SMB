#include "FireFlower.h"
#include "DxLib.h"
#include "SceneManager.h"

FireFlower::FireFlower(float tileX, float tileY, int type)
{
	pos = { tileX, tileY };
	spawnWait = SPAWN_WAIT_TIME;
	spawnPos = pos;
	state = IS_SPAWNING;
	speed.x = 1.0f;
	speed.y = 0.0f;
	isDead = false;
	renderLayer = RL_UNDER_TILE;
	objectType = OT_ITEM;
	itemType = type;
	size = { 16, 16 };
}

void FireFlower::Update(float cameraX)
{
	if (state == IS_SPAWNING)
	{
		if (SpawnUpdate())
		{
			state = IS_MOVING;
			renderLayer = RL_ITEM;
		}
	}
	else if (state == IS_MOVING)
	{
	}
}

void FireFlower::Render(float cameraX)
{
	if (spawnWait > 0)return;
	int drawX = static_cast<int>(pos.x) - static_cast<int>(cameraX);
	int drawY = static_cast<int>(pos.y);
	DrawBox(drawX, drawY, drawX + TILE_SIZE, drawY + TILE_SIZE, GetColor(255, 100, 100), true);
}
