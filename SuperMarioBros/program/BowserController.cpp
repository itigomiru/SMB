#include "BowserController.h"
#include "DxLib.h"
#include "ImageManager.h"
#include "Main.h"
#include "TileManager.h"
#include"ScoreEffect.h"
#include "EffectManager.h"
#include "EnemyDefeatedEffect.h"

Bowser::Bowser(float x, float y, float leftLimit, float rightLimit)
{
	pos.x = x;
	pos.y = y;

	speed.x = 0.0f;
	speed.y = 0.0f;

	hp = MAX_HP;

	size.w = BOWSER_W;
	size.h = BOWSER_H;

	tileManager = nullptr;

	objectType = Object::OT_ENEMY;
	renderLayer = Object::RL_ENEMY;

	moveLeftLimit = leftLimit;
	moveRightLimit = rightLimit;

	isDead = false;
	isGrounded = false;

	canSquashed = false;
	canDamage = true;

	action = ACTION_MOVE_LEFT;
	actionTimer = 60;
	jumpTimer = 0;
	hasJumped = false;
}

void Bowser::Update(float cameraX)
{
	if (isDead) return;

	if (actionTimer <= 0)
	{
		SelectAction();
	}

	switch (action)
	{
	case ACTION_MOVE_RIGHT:
		speed.x = BOWSER_MOVE_SPEED;
		break;

	case ACTION_MOVE_LEFT:
		speed.x = -BOWSER_MOVE_SPEED;
		break;

	case ACTION_BREATH:
		speed.x = 0.0f;
		break;
	}

	actionTimer--;

	jumpTimer--;

	if (jumpTimer <= 0)
	{
		if (isGrounded)
		{
			speed.y = -BOWSER_JUMP_POWER;
		}

		jumpTimer = 90 + GetRand(90);
	}

	ApplyGravity();
	Move();

	CheckOutOfScreen(cameraX);
}

void Bowser::SelectAction()
{
	int r = GetRand(2); // 0〜2

	bool canMoveLeft = pos.x + size.w > moveLeftLimit;
	bool canMoveRight = pos.x < moveRightLimit;

	hasJumped = false;

	if (r == 0 && canMoveRight)
	{
		action = ACTION_MOVE_RIGHT;
		actionTimer = 60;
	}
	else if (r == 1 && canMoveLeft)
	{
		action = ACTION_MOVE_LEFT;
		actionTimer = 60;
	}
	else
	{
		action = ACTION_BREATH;
		actionTimer = 90;
	}
}

void Bowser::ApplyGravity()
{
	speed.y += GRAVITY;

	if (speed.y > FALL_SPEED_MAX)
	{
		speed.y = FALL_SPEED_MAX;
	}
}

void Bowser::Move()
{
	pos.x += speed.x;
	pos.y += speed.y;

	int left = static_cast<int>(pos.x) / TILE_SIZE;
	int right = static_cast<int>(pos.x + size.w - 1) / TILE_SIZE;
	int bottom = static_cast<int>(pos.y + size.h - 1) / TILE_SIZE;

	if (tileManager->IsSolid(left, bottom) ||
		tileManager->IsSolid(right, bottom))
	{
		pos.y = static_cast<float>(bottom * TILE_SIZE - size.h);
		speed.y = 0.0f;
		isGrounded = true;
	}
	else
	{
		isGrounded = false;
	}
}

void Bowser::Render(float cameraX)
{
	if (isDead) return;

	int drawX = static_cast<int>(pos.x - cameraX);
	int drawY = static_cast<int>(pos.y);

	DrawBox(
		drawX,
		drawY,
		drawX + static_cast<int>(size.w),
		drawY + static_cast<int>(size.h),
		GetColor(255, 80, 80),
		TRUE
	);
}

void Bowser::OnSquashed()
{
}

void Bowser::Death(bool isRight, int score)
{
	isDead = true;
	EffectManager::GetInstance().AddEffect(std::make_unique<EnemyDefeatedEffect>(pos.x, pos.y,ET_BOWSER,isFacingRight));
	EffectManager::GetInstance().AddEffect(std::make_unique<ScoreEffect>(pos, score));
}

void Bowser::Damage()
{
	hp--;

	if (hp <= 0)
	{
		Death(isFacingRight, ScoreEffect::SCORE_5000);
	}
}
