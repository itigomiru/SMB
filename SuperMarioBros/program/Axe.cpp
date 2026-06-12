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
}

void Axe::Update(float cameraX)
{
}
void Axe::Render(float cameraX)
{
	int drawX = static_cast<int>(pos.x) - static_cast<int>(cameraX) - 1;
	int drawY = static_cast<int>(pos.y);
	DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_AXE), true);
	DrawGraph(drawX - 16, drawY + 16, ImageManager::GetInstance().GetImage(IMAGE_AXE_CHAIN), true);
}
