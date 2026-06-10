#include "LiftController.h"
#include "DxLib.h"
#include "ImageManager.h"
#include "Main.h"

Lift::Lift(float x, float y, float distance)
{
	pos.x = x;
	pos.y = y;

	startPos = pos;

	moveDistance = distance;
	moveX = 0.0f;

	speed.x = LIFT_SPEED;

	size.w = LIFT_W;
	size.h = LIFT_H;

	objectType = Object::OT_LIFT;
	renderLayer = Object::RL_LIFT;
	isDead = false;
}

void Lift::Update(float cameraX)
{
	float oldX = pos.x;

	pos.x += speed.x;

	if (pos.x > startPos.x + moveDistance)
	{
		pos.x = startPos.x + moveDistance;
		speed.x = -LIFT_SPEED;
	}

	if (pos.x < startPos.x)
	{
		pos.x = startPos.x;
		speed.x = LIFT_SPEED;
	}

	moveX = pos.x - oldX;
}

void Lift::Render(float cameraX)
{
	int imgHandle = ImageManager::GetInstance().GetImage(IMAGE_LIFT);

	int drawX = static_cast<int>(pos.x - cameraX);
	int drawY = static_cast<int>(pos.y);

	DrawGraph(drawX, drawY, imgHandle, TRUE);
	
}

