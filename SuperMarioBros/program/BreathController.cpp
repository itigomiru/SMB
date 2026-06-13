#include "BreathController.h"
#include "DxLib.h"
#include "ImageManager.h"
#include "Main.h"
#include "TileManager.h"
#include "ScoreEffect.h"
#include "EffectManager.h"
#include "EnemyDefeatedEffect.h"

Breath::Breath(bool right, Float2 position, float target, float moveSpeed)
{
	pos = position;

	isRight = right;
	targetY = target;

	if (isRight)
	{
		speed.x = moveSpeed;
	}
	else
	{
		speed.x = -moveSpeed;
	}
	speed.y = 0.0f;

	size.w = BREATH_W;
	size.h = BREATH_H;

	objectType = Object::OT_ENEMY_BULLET;
	renderLayer = Object::RL_ENEMY;

	isDead = false;

	state = BREATH_MOVE_TO_TARGET_Y;
}


void Breath::Update(float cameraX)
{
	if (isDead) return;

	if (state == BREATH_MOVE_TO_TARGET_Y)
	{
		if (pos.y > targetY)
		{
			pos.y -= BREATH_Y_SPEED;
			pos.x += speed.x / 2.0f; // 少し横に動きながら上昇

			if (pos.y <= targetY)
			{
				pos.y = targetY;
				state = BREATH_FLY_STRAIGHT;
			}
		}
		else if (pos.y < targetY)
		{
			pos.y += BREATH_Y_SPEED;

			if (pos.y >= targetY)
			{
				pos.y = targetY;
				state = BREATH_FLY_STRAIGHT;
			}
		}
		else
		{
			state = BREATH_FLY_STRAIGHT;
		}
	}

	if (state == BREATH_FLY_STRAIGHT)
	{
		pos.x += speed.x;
	}

	if (pos.x < cameraX - TILE_SIZE ||
		pos.x > cameraX + SCREEN_W + TILE_SIZE)
	{
		isDead = true;
	}
}

void Breath::Render(float cameraX)
{
	if (isDead) return;

	int drawX = static_cast<int>(pos.x - cameraX);
	int drawY = static_cast<int>(pos.y);
	DrawRectGraph(drawX,drawY,0,0,BREATH_W,	BREATH_H,ImageManager::GetInstance().GetImage(IMAGE_BULLET_BREATH),	TRUE,isRight);

	// 当たり判定確認用
	/*DrawBox(
		static_cast<int>(pos.x - cameraX),
		static_cast<int>(pos.y),
		static_cast<int>(pos.x - cameraX + size.w),
		static_cast<int>(pos.y + size.h),
		GetColor(0, 255, 0),
		FALSE
	);*/
}