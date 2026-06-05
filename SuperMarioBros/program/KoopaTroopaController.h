#pragma once
#include "Enemy.h"
#include "Object.h"

class TileManager;

class KoopaTroopa : public Enemy
{
public:
	enum KoopaTroopaState
	{
		STATE_WALK,
		STATE_SHELL_STOP,
		STATE_SHELL_ROLL,
		STATE_SHELL_WAKEUP,
	};

	KoopaTroopa();
	void Update(float cameraX) override;
	void Render(float cameraX) override;
	void Move() override;
	void ApplyGravity() override;

	KoopaTroopaState GetState() const { return KoopaTroopaState; }
	int GetEnemyType() const override { return Enemy::ET_KOOPATROOPA; }

	void SetPosition(float x, float y);
	void SetTileManager(TileManager* tm);

	void OnSquashed() override;
	void OnKicked(float marioX);
	void Death() override;
private:
	
	KoopaTroopaState KoopaTroopaState;
	int wakeUpTimer;

	const int WAKEUP_TIME = 480; 
	const int SHELL_START_TIME = 80;

	Float2 shakeOffset;

	const float SHELL_SPEED = 4.0f;

	const float HEIGHT = 16.0f;
	const float WIDTH = 16.0f;

	const Float2 VEL_MAX = { 5.0f, 10.0f };
	Float2 prevPos;

	TileManager* tileManager = nullptr;

	void CheckCollisionX();
	void CheckCollisionY();
	bool CheckGround();
};
