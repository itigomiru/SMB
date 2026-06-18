#include "Star.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "ImageManager.h"

Star::Star(float tileX, float tileY, int type)
{
	pos = { tileX, tileY };
	hitBoxPos = pos;
	spawnWait = SPAWN_WAIT_TIME;
	spawnPos = pos;
	state = IS_SPAWNING;
	speed.x = MOVE_SPEED;
	speed.y = 0.0f;
	isDead = false;
	renderLayer = RL_UNDER_TILE;
	objectType = OT_ITEM;
	itemType = type;

	size = { 16, 16 };
	hitBoxSize = size;
}

void Star::Update(float cameraX)
{
	CheckOutOfScreen(cameraX);
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
		speed.y += SceneManager::GetInstance().GRAVITY / 2.0f;

		pos.x += speed.x;
		CheckCollisionX();

		pos.y += speed.y;
		CheckCollisionY();
	}

	animationCounter = (animationCounter + 1) % (ANIM_SPEED * ANIM_FRAMES);
	hitBoxPos = pos;
	hitBoxSize = size;
}

void Star::Render(float cameraX)
{
	if (spawnWait > 0)return;
	int drawX = static_cast<int>(pos.x) - static_cast<int>(cameraX);
	int drawY = static_cast<int>(pos.y);
	int currentFrame = animationCounter / ANIM_SPEED;

	int srcX = currentFrame * size.w;
	int srcY = 0;

	int imgHandle = ImageManager::GetInstance().GetImage(IMAGE_ITEM_STAR);

	DrawRectGraph(drawX, drawY, srcX, srcY, size.w, size.h, imgHandle, TRUE, FALSE);
}
void Star::CheckCollisionX()
{
	int px = static_cast<int>(pos.x);

	int py = static_cast<int>(pos.y);

	int top = py / TILE_SIZE;

	int bottom = (py + size.h - 1) / TILE_SIZE;
	//=========================================================
	// 右移動
	//=========================================================

	if (speed.x > 0.0f)
	{
		int right = (px + size.w) / TILE_SIZE;

		if (tileManager->IsSolid(right, top) || tileManager->IsSolid(right, bottom))
		{
			pos.x = static_cast<float>(right * TILE_SIZE - size.w);

			speed.x *= -1;
		}
	}

	//=========================================================
	// 左移動
	//=========================================================

	else if (speed.x < 0.0f)
	{
		int left = px / TILE_SIZE;

		if (tileManager->IsSolid(left, top) || tileManager->IsSolid(left, bottom))
		{
			pos.x = static_cast<float>((left + 1) * TILE_SIZE);

			speed.x *= -1;
		}
	}
}


void Star::CheckCollisionY()
{
	int px = static_cast<int>(pos.x);
	int py = static_cast<int>(pos.y);
	int left = px / TILE_SIZE;
	int right = (px + size.w - 1) / TILE_SIZE;
	if (speed.y > 0.0f)
	{
		int bottom =
			(py + size.h - 1)
			/ TILE_SIZE;

		if (tileManager->IsSolid(left, bottom) || tileManager->IsSolid(right, bottom))
		{
			pos.y =
				static_cast<float>(
					bottom * TILE_SIZE - size.h);

			speed.y = -3.5f;

		}
	}
}
