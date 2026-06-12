#include "BowserController.h"
#include "DxLib.h"
#include "ImageManager.h"
#include "Main.h"
#include "TileManager.h"
#include "ScoreEffect.h"
#include "EffectManager.h"
#include "EnemyDefeatedEffect.h"
#include "BreathController.h"
#include "Player.h"
#include "ObjectManager.h"


Bowser::Bowser(float x, float y, float leftLimit, float rightLimit)
{
	pos.x = x;
	pos.y = y;

	speed.x = 0.0f;
	speed.y = 0.0f;

	hasBreath = false;
	breathTimer = 0;
	breathCoolDown = 0;

	hp = MAX_HP;

	size.w = BOWSER_W;
	size.h = BOWSER_H;

	tileManager = nullptr;
	objectManager = nullptr;
	player = nullptr;


	objectType = Object::OT_ENEMY;
	renderLayer = Object::RL_ENEMY;

	moveLeftLimit = leftLimit;
	moveRightLimit = rightLimit;

	isFacingRight = false;

	isDead = false;
	isGrounded = false;

	canSquashed = false;
	canDamage = true;

	action = ACTION_MOVE_LEFT;
	actionTimer = 60;
	jumpTimer = 0;
	hasJumped = false;

	animeFrame = 0;
	animeTimer = 0;
}

void Bowser::Update(float cameraX)
{
	if (isDead) return;

	if (player != nullptr)
	{
		isFacingRight = player->pos.x > pos.x;
	}

	if (actionTimer <= 0)
	{
		SelectAction();
	}

	if (breathCoolDown > 0)
	{
		breathCoolDown--;
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

		if (!hasBreath && objectManager != nullptr)
		{
			Float2 breathPos;
			breathPos.x = pos.x;
			breathPos.y = pos.y + 4.0f;

			float targetY = pos.y + 16.0f;

			if (player != nullptr )
			{
				isFacingRight = player->pos.x > pos.x;
			}

			if (isFacingRight)
			{
				breathPos.x = pos.x + size.w; // ブレスの初期位置を調整
			}
			else
			{
				breathPos.x = pos.x;
			}

			if (player != nullptr && player->pos.y < pos.y + SIZE_H_HALF)
			{
				targetY = pos.y;
			}

			objectManager->AddObject(std::make_unique<Breath>(
				isFacingRight,
				breathPos,
				targetY,
				2.0f
			));

			hasBreath = true;
			breathCoolDown = BREATH_COOLDOWN;
		}
		break;
	}

	animeTimer++;

	if (animeTimer >= BOWSER_ANIME_INTERVAL)
	{
		animeTimer = 0;
		animeFrame++;

		if (animeFrame >= 2)
		{
			animeFrame = 0;
		}

	}

	ApplyGravity();
	Move();

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

	CheckOutOfScreen(cameraX);
}

void Bowser::SelectAction()
{
	hasBreath = false;
	hasJumped = false;

	while (true)
	{
		int r = GetRand(2); // 0〜2

		bool canMoveLeft = pos.x > moveLeftLimit;
		bool canMoveRight = pos.x + size.w < moveRightLimit;

		if (r == 0 && canMoveRight)
		{
			action = ACTION_MOVE_RIGHT;
			actionTimer = 60;
			break;
		}
		else if (r == 1 && canMoveLeft)
		{
			action = ACTION_MOVE_LEFT;
			actionTimer = 60;
			break;
		}
		else if (r == 2 && breathCoolDown <= 0)
		{
			action = ACTION_BREATH;
			actionTimer = 90;
			break;
		}
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

	int imgHandle;

	if (action == ACTION_BREATH)
	{
		imgHandle = ImageManager::GetInstance().GetImage(IMAGE_ENEMY_BOWSER_BREATH);
	}
	else
	{
		imgHandle = ImageManager::GetInstance().GetImage(IMAGE_ENEMY_BOWSER_WALK);
	}

	int drawX = static_cast<int>(pos.x - cameraX);
	int drawY = static_cast<int>(pos.y);

	int srcX = animeFrame * BOWSER_FRAME_W;

	DrawRectGraph(drawX,drawY,srcX,0,BOWSER_FRAME_W,BOWSER_FRAME_H,imgHandle,TRUE,isFacingRight);
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
