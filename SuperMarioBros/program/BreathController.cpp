#include "BreathController.h"
#include "DxLib.h"
#include "ImageManager.h"
#include "Main.h"
#include "TileManager.h"
#include "ScoreEffect.h"
#include "EffectManager.h"
#include "EnemyDefeatedEffect.h"

Breath::Breath(bool right, bool up, float width, Float2 position, float moveSpeed)
{
	pos = position;

	isRight = right;
	isUp = up;

	startY = pos.y;
	riseWidth = width;

	speed.x = isRight ? moveSpeed : -moveSpeed;
	speed.y = isUp ? -1.0f : 1.0f;

	size.w = BREATH_W;
	size.h = BREATH_H;

	objectType = Object::OT_ENEMY_BULLET;
	renderLayer = Object::RL_ENEMY;

	isDead = false;
}

void Breath::Update(float cameraX)
{
	if (isDead) return;

	pos.x += speed.x;
	pos.y += speed.y;

	if (pos.y < startY - riseWidth)
	{
		pos.y = startY - riseWidth;
		speed.y = 1.0f;
	}

	if (pos.y > startY + riseWidth)
	{
		pos.y = startY + riseWidth;
		speed.y = -1.0f;
	}

	if (pos.x < cameraX - TILE_SIZE || pos.x > cameraX + SCREEN_W + TILE_SIZE)
	{
		isDead = true;
	}
}

void Breath::Render(float cameraX)
{
	if (isDead) return;

	int drawX = static_cast<int>(pos.x - cameraX);
	int drawY = static_cast<int>(pos.y);

	DrawGraph(
		drawX,
		drawY,
		ImageManager::GetInstance().GetImage(IMAGE_BULLET_BREATH),
		TRUE
	);
}