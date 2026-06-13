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
	animeFrame = 0;
	animeTimer = 0;
}

void Axe::Update(float cameraX)
{
	animeTimer++;

	if (animeTimer >= AXE_ANIME_INTERVAL)
	{
		animeTimer = 0;
		animeFrame++;

		if (animeFrame >= AXE_FRAME_MAX)
		{
			animeFrame = 0;
		}
	}
}
void Axe::Render(float cameraX)
{
	int drawX = static_cast<int>(pos.x) - static_cast<int>(cameraX) - 1;
	int drawY = static_cast<int>(pos.y);

	int srcX = animeFrame * AXE_FRAME_W;

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
