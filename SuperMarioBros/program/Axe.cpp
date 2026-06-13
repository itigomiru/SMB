#include "Axe.h"
#include "DxLib.h"
#include "ImageManager.h"
#include"ScoreEffect.h"
Axe::Axe()
{
	pos = { 2257.0f,128.0f };
	size = { 15.0f, 16.0f };
	objectType = OT_GOAL;
	renderLayer = RL_GOAL;
	isDead = false;
	animationCounter = 0;
	animWaitCounter = 0;
}

void Axe::Update(float cameraX)
{
	if (animWaitCounter > 0)
	{
		animWaitCounter--;
	}
	else
	{
		int prevFrame = animationCounter / AXE_ANIM_SPEED;

		animationCounter =
			(animationCounter + 1) % (AXE_ANIM_SPEED * AXE_ANIM_FRAMES);

		int nextFrame = animationCounter / AXE_ANIM_SPEED;

		if (prevFrame != 0 && nextFrame == 0)
		{
			animWaitCounter = AXE_ANIM_WAIT_TIME;
		}
	}
}

void Axe::Render(float cameraX)
{
	int drawX = static_cast<int>(pos.x) - static_cast<int>(cameraX) - 1;
	int drawY = static_cast<int>(pos.y);

	int animFrame = animationCounter / AXE_ANIM_SPEED;
	int srcX = animFrame * AXE_FRAME_W;

	DrawRectGraph(
		drawX,
		drawY,
		srcX,
		0,
		AXE_FRAME_W,
		AXE_FRAME_H,
		ImageManager::GetInstance().GetImage(IMAGE_AXE),
		true
	);

	DrawGraph(
		drawX - 16,
		drawY + 16,
		ImageManager::GetInstance().GetImage(IMAGE_AXE_CHAIN),
		true
	);
}