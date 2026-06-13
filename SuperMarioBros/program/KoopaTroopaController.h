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
	int comboCount = 0;

	KoopaTroopa();
	void Update(float cameraX) override;
	void Render(float cameraX) override;
	void Move() override;
	void ApplyGravity() override;

	KoopaTroopaState GetState() const { return koopaTroopaState; }
	int GetEnemyType() const override { return Enemy::ET_KOOPATROOPA; }

	void SetPosition(float x, float y);
	void SetTileManager(TileManager* tm);

	void OnSquashed() override;
	void OnKicked(float marioX);
	void Death(bool isRight,int score) override;
private:
	
	KoopaTroopaState koopaTroopaState;
	int wakeUpTimer;
	int walkFrame;
	int wakeFrame;

	const int WAKEUP_TIME = 480; 
	const int SHELL_START_TIME = 80;

	int animationCounter = 0;
	const int ANIM_SPEED_WALK = 14;
	const int ANIM_SPEED_WAKE = 12; 
	const int WALK_FRAMES = 2;

	Float2 shakeOffset;

	const float SHELL_SPEED = 4.0f;

	const float HEIGHT = 24.0f;
	const float WIDTH = 16.0f;
	const float SHELL_HEIGHT = 16.0f;

	const Float2 SPEED = { 0.5f, 4.0f };
	Float2 prevPos;

	TileManager* tileManager = nullptr;
	

	void CheckCollisionX();
	void CheckCollisionY();
	bool CheckGround();
};
