#pragma once
#include "Enemy.h"
#include "Object.h"

class TileManager;

class Goomba : public Enemy
{
public:
	Goomba();
	void Update(float cameraX) override;
	void Render(float cameraX) override;
	void Move() override;
	void ApplyGravity() override;

	int GetEnemyType() const override { return Enemy::ET_GOOMBA; }

	void SetPosition(float x, float y);
	void SetTileManager(TileManager* tm);

	void OnSquashed();
	void Death() override;
private:
	enum GoombaState
	{
		STATE_WALK,
		STATE_SQUASHED,
	};

	GoombaState goombaState = STATE_WALK;

	int animationCounter = 0;
	int squashTimer = 0;

	const int ANIM_SPEED = 14;
	const int ANIM_FRAMES = 2;
	const int SQUASH_DURATION = 30;

	const float HEIGHT = 16.0f;
	const float WIDTH = 16.0f;

	const Float2 SPEED = { 0.5f, 7.0f };
	Float2 prevPos;

	TileManager* tileManager = nullptr;

	void CheckCollisionX();
	void CheckCollisionY();
	bool CheckGround();
};
