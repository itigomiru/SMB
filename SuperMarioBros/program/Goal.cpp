#include "Goal.h"
#include "DxLib.h"
#include "ImageManager.h"
#include"ScoreEffect.h"
Goal::Goal()
{
	pos = { 3169.0f,32.0f };
	hitBoxPos = pos;
	size = { 16.0f, 176.0f };
	hitBoxSize = size;
	flagPos = { 3160.0f, 48.0f };
	objectType = OT_GOAL;
	renderLayer = RL_GOAL;
	isDead = false;
	isFlagMoving = false;
	isFlagEnd = false;
}

void Goal::Update(float cameraX)
{
	if (isFlagMoving && !isFlagEnd)
	{
		flagPos.y += FLAG_DOWN_SPEED;

		if (flagPos.y >= FLAG_END_Y)
		{
			flagPos.y = FLAG_END_Y;
			isFlagMoving = false;
			isFlagEnd = true;
		}
	}
}

void Goal::Render(float cameraX)
{
	int drawX = static_cast<int>(pos.x) - static_cast<int>(cameraX) -1;
	int drawY = static_cast<int>(pos.y);
	int flagDrawX = static_cast<int>(flagPos.x) - static_cast<int>(cameraX);
	int flagDrawY = static_cast<int>(flagPos.y);
	DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_GOAL),true);
	DrawGraph(flagDrawX, flagDrawY, ImageManager::GetInstance().GetImage(IMAGE_GOAL_FLAG), true);
}
int Goal::GetScore(float playerY)
{
	float rate = (playerY - pos.y) / size.h;

	if (rate < 0.2f) return ScoreEffect::SCORE_5000;
	if (rate < 0.4f) return ScoreEffect::SCORE_2000;
	if (rate < 0.6f) return ScoreEffect::SCORE_800;
	if (rate < 0.8f) return ScoreEffect::SCORE_400;

	return ScoreEffect::SCORE_100;
}

void Goal::StartFlagMove()
{
	if (isFlagEnd) return;

	isFlagMoving = true;
}