#include "FirebarController.h"
#include "DxLib.h"
#include "ImageManager.h"
#include "Main.h"
#include <cmath>

Firebar::Firebar(float tileX, float tileY, float distance, bool isClockwise, TileManager* tm)
{
	m_centerPos.x = tileX * TILE_SIZE + (TILE_SIZE / 2.0f);
	m_centerPos.y = tileY * TILE_SIZE + (TILE_SIZE / 2.0f);

	m_distance = distance; 
	m_isClockwise = isClockwise;
	m_angleDegree = 0.0f;
	m_ballRotateDegree = 0.0f;

	tileManager = tm;
	objectType = Object::OT_ENEMY;
	size = { 8.0f, 8.0f };
	isDead = false;
	canSquashed = false;
	canDamage = true;
}

void Firebar::Update(float cameraX)
{
	if (isDead) return;

	if (m_isClockwise)
	{
		m_angleDegree += ROTATION_SPEED;
	}
	else
	{
		m_angleDegree -= ROTATION_SPEED;
	}

	if (m_angleDegree >= 360.0f)
	{
		m_angleDegree -= 360.0f;
	}
	if (m_angleDegree < 0.0f)
	{
		m_angleDegree += 360.0f;
	}

	m_ballRotateDegree += 24.0f;

	if (m_ballRotateDegree >= 360.0f)
	{
		m_ballRotateDegree -= 360.0f;
	}

	float dirX = cosf(TO_RADIAN(m_angleDegree));
	float dirY = sinf(TO_RADIAN(m_angleDegree));

	for (int i = 0; i < FIREBAR_NUM; i++)
	{
		float distance = FIREBAR_INTERVAL * i;

		m_ballPos[i].x = m_centerPos.x + dirX * distance - FIREBALL_HALF_SIZE;
		m_ballPos[i].y = m_centerPos.y + dirY * distance - FIREBALL_HALF_SIZE;
	}

	pos.x = m_centerPos.x - size.w / 2.0f;
	pos.y = m_centerPos.y - size.h / 2.0f;
}

bool Firebar::HitPlayer(Object* player)
{
	for (int i = 0; i < FIREBAR_NUM; i++)
	{
		float fireLeft = m_ballPos[i].x;
		float fireRight = m_ballPos[i].x + size.w;
		float fireTop = m_ballPos[i].y;
		float fireBottom = m_ballPos[i].y + size.h;

		float playerLeft = player->pos.x;
		float playerRight = player->pos.x + player->size.w;
		float playerTop = player->pos.y;
		float playerBottom = player->pos.y + player->size.h;

		if (fireLeft < playerRight &&
			fireRight > playerLeft &&
			fireTop < playerBottom &&
			fireBottom > playerTop)
		{
			return true;
		}
	}
	return false;
}


void Firebar::Render(float cameraX)
{
	if(isDead) return;

	int imgHandle = ImageManager::GetInstance().GetImage(IMAGE_FIRE_BALL);

	float ballRadian = TO_RADIAN(m_ballRotateDegree);
	
	for (int i = 0; i < FIREBAR_NUM; i++)
	{
		
		int drawX = static_cast<int>(m_ballPos[i].x - cameraX);
		int drawY = static_cast<int>(m_ballPos[i].y);

		DrawRectRotaGraph(drawX +FIREBALL_HALF_SIZE , drawY + FIREBALL_HALF_SIZE, 0, 0, 8, 8, 1.0, ballRadian, imgHandle, TRUE, FALSE);
	}
}

void Firebar::OnSquashed() {}
void Firebar::Death(bool isRight,int score) {}
void Firebar::Move(){}
void Firebar::ApplyGravity(){}