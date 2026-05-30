#include "Fireball.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "TileManager.h"
#include "ObjectManager.h"
#include "Enemy.h"
#include "EffectManager.h"
#include "Hit.h"

Fireball::Fireball(Float2 pos, bool isFacingRight, TileManager* tm, ObjectManager* om)
{
	this->pos = pos;
	this->tileManager = tm;
	this->objectManager = om;

	objectType = OT_FIREBALL;
	size = { 8.0f, 8.0f };
	speed.x = isFacingRight ? MOVE_SPEED : -MOVE_SPEED;
	speed.y = 0;
	renderLayer = RL_PLAYER;
}

void Fireball::Update(float cameraX)
{

	ApplyGravity();

	MoveX();
	CheckCollisionX();

	MoveY();
	CheckCollisionY();

	CheckCollisionWithEnemies();

	if (bounceCount >= MAX_BOUNCES || CheckInScreen(cameraX))isDead = true;
}

void Fireball::Render(float cameraX)
{
	int drawX = static_cast<int>(pos.x - cameraX);
	int drawY = static_cast<int>(pos.y);
	DrawBox(drawX, drawY, drawX + size.w, drawY + size.h, GetColor(255, 0, 0), true);
}

void Fireball::ApplyGravity()
{
	speed.y += SceneManager::GetInstance().GRAVITY;
	if (speed.y > VEL_MAX.y)
	{
		speed.y = VEL_MAX.y;
	}
}

void Fireball::MoveX()
{
	pos.x += speed.x;
}

void Fireball::MoveY()
{
	pos.y += speed.y;
}

void Fireball::CheckCollisionX()
{
	int px = static_cast<int>(pos.x);
	int py = static_cast<int>(pos.y);
	int top = py / TILE_SIZE;
	int bottom = (py + size.h - 1) / TILE_SIZE;

	if (speed.x > 0.0f)
	{
		int right = (px + size.w) / TILE_SIZE;
		if (tileManager->IsSolid(right, top) || tileManager->IsSolid(right, bottom))
		{
			pos.x = static_cast<float>(right * TILE_SIZE - size.w);
			speed.x *= -1; // Reverse direction
			bounceCount++;
		}
	}
	else if (speed.x < 0.0f)
	{
		int left = px / TILE_SIZE;
		if (tileManager->IsSolid(left, top) || tileManager->IsSolid(left, bottom))
		{
			pos.x = static_cast<float>((left + 1) * TILE_SIZE);
			speed.x *= -1; // Reverse direction
			bounceCount++;
		}
	}
}

void Fireball::CheckCollisionY()
{
	int px = static_cast<int>(pos.x);
	int py = static_cast<int>(pos.y);
	int left = px / TILE_SIZE;
	int right = (px + size.w - 1) / TILE_SIZE;

	if (speed.y > 0.0f)
	{
		int bottom = (py + size.h) / TILE_SIZE;
		if (tileManager->IsSolid(left, bottom) || tileManager->IsSolid(right, bottom))
		{
			pos.y = static_cast<float>(bottom * TILE_SIZE - size.h);
			speed.y = -JUMP_POWER; // Bounce
			bounceCount++;
		}
	}
	else if (speed.y < 0.0f)
	{
		int top = py / TILE_SIZE;
		if (tileManager->IsSolid(left, top) || tileManager->IsSolid(right, top))
		{
			pos.y = static_cast<float>((top + 1) * TILE_SIZE);
			speed.y = 0;
		}
	}
}

void Fireball::CheckCollisionWithEnemies()
{
	for (auto& obj : objectManager->GetObjects())
	{
		if (obj->objectType == OT_ENEMY)
		{
			if (objectManager->HitObjects(this, obj.get()))
			{
				isDead = true;
				//エフェクトを作成
				break;
			}
		}
	}
}

bool Fireball::CheckInScreen(float cameraX)
{
	int screenLeft = static_cast<int>(cameraX) - size.w;
	int screenRight = static_cast<int>(cameraX) + SCREEN_W + size.w;
	return pos.x < screenLeft || pos.x > screenRight;
}