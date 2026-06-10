#pragma once
#include "Enemy.h"

class TileManager;

class Firebar : public Enemy
{
public:
	Firebar(float tileX, float tileY, float distance, bool isClockwise, TileManager* tm);

	void Update(float cameraX) override;
	void Render(float cameraX) override;

	int GetEnemyType() const override { return Enemy::ET_FIREBAR; }

	void OnSquashed() override;
	void Death(bool isRight,int score) override;

	void Move() override;
	void ApplyGravity() override;

	bool HitPlayer(Object* player);

private:

	TileManager* tileManager = nullptr;

	Float2 m_centerPos;
	float m_distance;
	bool m_isClockwise;
	float m_angleDegree;

	float m_ballRotateDegree;
	static const int FIREBALL_SIZE = 8;
	static const int FIREBALL_HALF_SIZE = FIREBALL_SIZE / 2;

	static const int FIREBAR_NUM = 6;
	const float ROTATION_SPEED = 2.0f;
	const float FIREBAR_INTERVAL = 9.0f;

	Float2 m_ballPos[FIREBAR_NUM];

	
};