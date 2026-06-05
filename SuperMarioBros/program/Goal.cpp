#include "Goal.h"
#include "DxLib.h"
Goal::Goal()
{
	pos = { 3172.0f,32.0f };
	size = { 8.0f, 176.0f };
	objectType = OT_GOAL;
	renderLayer = RL_GOAL;
	isDead = false;
}

void Goal::Update(float cameraX)
{
	// ゴールは特に更新することがないため、ここでは何もしません。
}
void Goal::Render(float cameraX)
{
	int drawX = static_cast<int>(pos.x) - static_cast<int>(cameraX);
	int drawY = static_cast<int>(pos.y);
	DrawBox(drawX, drawY, drawX + size.w, drawY + size.h, GetColor(0, 255, 0), true);
}
int Goal::GetScore(float playerY)
{
	float rate = (playerY - pos.y) / size.h;

	if (rate < 0.2f) return 5000;
	if (rate < 0.4f) return 2000;
	if (rate < 0.6f) return 800;
	if (rate < 0.8f) return 400;

	return 100;
}