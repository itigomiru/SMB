#include "FireFlower.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "ImageManager.h"

FireFlower::FireFlower(float tileX, float tileY, int type)
{
	pos = { tileX, tileY };
	hitBoxPos = pos;
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
	hitBoxSize = size;
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

	animationCounter = (animationCounter + 1) % (ANIM_SPEED * ANIM_FRAMES);
	hitBoxPos = pos;
	hitBoxSize = size;
}

void FireFlower::Render(float cameraX)
{
	if (spawnWait > 0)return;
	int drawX = static_cast<int>(pos.x) - static_cast<int>(cameraX);
	int drawY = static_cast<int>(pos.y);

	int currentFrame = animationCounter / ANIM_SPEED;

	int srcX = currentFrame * size.w;
	int srcY = 0; 

	int imgHandle = ImageManager::GetInstance().GetImage(IMAGE_ITEM_FIREFLOWER);

	DrawRectGraph(drawX, drawY, srcX, srcY, size.w, size.h, imgHandle, TRUE, FALSE);
}
