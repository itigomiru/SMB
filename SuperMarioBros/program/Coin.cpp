#include "Coin.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "ImageManager.h"

Coin::Coin(float x, float y)
{
	pos = { x, y };
	state = IS_MOVING;
	speed.x = 1.0f;
	speed.y = 0.0f;
	isDead = false;
	renderLayer = RL_UNDER_TILE;
	objectType = OT_ITEM;
	itemType = TileManager::ITEM_COIN;
	size = { 16, 16 };
}

void Coin::Update(float cameraX)
{
	if (animWaitCounter > 0)
	{
		animWaitCounter--;
	}
	else
	{
		int prevFrame = animationCounter / ANIM_SPEED;
		animationCounter = (animationCounter + 1) % (ANIM_SPEED * ANIM_FRAMES);
		int nextFrame = animationCounter / ANIM_SPEED;

		if (prevFrame != 0 && nextFrame == 0)
		{
			animWaitCounter = ANIM_WAIT_TIME;
		}
	}
}

void Coin::Render(float cameraX)
{
	int drawX = static_cast<int>(pos.x) - static_cast<int>(cameraX);
	int drawY = static_cast<int>(pos.y);

	int animFrame = animationCounter / ANIM_SPEED;

	int srcX = animFrame * TILE_SIZE;

	int imgHandle = ImageManager::GetInstance().GetImage(IMAGE_UNDERGROUND_COIN);

	DrawRectGraph(drawX, drawY, srcX, 0, size.w, size.h, imgHandle, TRUE, FALSE);
}
