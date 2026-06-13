#include "LiftController.h"
#include "DxLib.h"
#include "ImageManager.h"
#include "Main.h"

Lift::Lift(float x, float y, float distance)
{
	pos.x = x;
	pos.y = y;

	startPos = pos;

	moveMax = distance;
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
	// 1. 前のフレームの位置を記録
	float oldX = pos.x;

	// 2. 角度（時間）を進める（速度調整用）
	angle += 0.02f;

	float sin01 = (sinf(angle) + 1.0f) * 0.5f;

	// 4. 0のときstartPos.x、1のときstartPos.x + moveDistance になる
	pos.x = startPos.x + (sin01 * moveMax);

	// 5. 前のフレームからの移動量を計算
	moveX = pos.x - oldX;
}

void Lift::Render(float cameraX)
{
	int imgHandle = ImageManager::GetInstance().GetImage(IMAGE_LIFT);

	int drawX = static_cast<int>(pos.x - cameraX);
	int drawY = static_cast<int>(pos.y);

	DrawGraph(drawX, drawY, imgHandle, TRUE);
	
}

