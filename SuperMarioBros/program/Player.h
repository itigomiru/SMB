#pragma once
#include "Object.h"

class Stage;
class TileManager;
class ObjectManager;
class Enemy;

class Player : public Object
{
public:
	Player(Float2 position);
	void Init(Float2 postion);
	void Update(float cameraX) override;
	void Render(float cameraX) override;

	void SetTileManager(TileManager* tm);
	void SetObjectManager(ObjectManager* om);
	void SetStage(Stage* st);
	void GetSuperMashroom();
	void GetFireFlower();
	void Get1UpMushroom();
	void GetStar();

	bool CheckSquashEnemy(Enemy* enemy);
	void PowerUpUpdate();
	void DeathUpdate();
	void GoalUpdate();
	void OnGoal(float poleCenterX); 

	void Damage();

	void LandingOnGround();

	bool isOnLift;

	int deathTimer;
	int freezeTimer;
	int invincibleTimer;
	int starTimer;

private:
	const float SMALL_H = 16.0f;
	const float SUPER_H = 32.0f;
	const float WIDTH = 16.0f;
	const float MOVE_ACCEL = 0.05f;	//加速度
	const float FRICTION = 0.04f;	//摩擦(キーを入れない時の減速度)
	const float JUMP_POWER = 5.0f;
	const int FIRE_COOLDOWN_TIME = 5;
	const int FIREBALL_MAX = 2;
	const float DASH_JUDGE_SPEED = 1.8f;
	const float DASH_JUNP_POWER_MULTIPLIER = 1.05f;
	const float OVERLAP_JUDGE = 6.0f;
	const int INVINCIBLE_TIME = 120;
	const int DEATH_TIME = 120;
	const int POWER_UP_TIME = 60;
	const int STAR_TIME = 600;

	const Float2 SPEED_MAX = { 2.0f, 7.0f };
	const float DASH_SPEED_MAX = 3.0f;

	const float SQUASH_BOUNCE_POWER = 4.5f;

	bool isGround;//地面にいるかどうか
	bool isJumping;
	bool isAnimJamping;
	int animeCount = 0;

	bool CheckLift();

	int state;
	bool isFacingRight;

	int oldState;
	int newState;
	bool isChangingState = false;
	int comboCount = 0;

	Float2 prevPos;


	bool isCrouching;
	bool isTryingToStand;
	float standPushDir;
	int fireCooldown;
	int firePoseTimer;
	const int FIRE_POSE_TIME = 12;

	float deathSpeedY;
	bool isFallenDeath;
	const float DEATH_JUMP_POWER = 7.0f;

	bool isGoal;       // ゴール演出中かどうか
	int goalPhase;     // ゴール演出の進行状態 (0: ポール降下中, 1: 右へ移動中, 2: 城到達)
	enum GoalPhase
	{
		GP_DOWN,
		GP_WALK,
		GP_CASTLE,
	};
	int fireballCount;
	enum PlayerState
	{
		SMALL,
		SUPER,
		FIRE,
	};

	TileManager* tileManager = nullptr;
	ObjectManager* objectManager = nullptr;
	Stage* stage = nullptr;

	void Input();
	void MoveX();
	void MoveY();
	void Jump();
	void ApplyGravity();
	void CheckCollisionX();
	void CheckCollisionY();
	bool CheckGround();

	void Death();

	void UpdatePlayerSize();
	bool CheckCanStand();
	void UpdateStandPush();

	void RenderSmall(float cameraX);
	void RenderBig(float cameraX);
	void RenderFire(float cameraX);
	void RenderStar(float cameraX);

	void PipeCheck();

	
};

