#pragma once
#include "Object.h"

class TileManager;
class ObjectManager;
class Enemy;

class Player : public Object
{
public:
	Player();
	void Init();
	void Update(float cameraX) override;
	void Render(float cameraX) override;

	void SetTileManager(TileManager* tm);
	void SetObjectManager(ObjectManager* om);
	void GetSuperMashroom();
	void GetFireFlower();
	void Get1UpMushroom();

	bool CheckSquashEnemy(Enemy* enemy);


private:
	const float SMALL_H = 16.0f;
	const float SUPER_H = 32.0f;
	const float WIDTH = 16.0f;
	const float MOVE_ACCEL = 0.05f;	//加速度
	const float FRICTION = 0.2f;	//摩擦(キーを入れない時の減速度)
	const float JUMP_POWER = 5.0f;
	const int FIRE_COOLDOWN_TIME = 5;
	const int FIREBALL_MAX = 2;
	const float DASH_JUDGE_SPEED = 1.8f;
	const float DASH_JUNP_POWER_MULTIPLIER = 1.05f;
	const float OVERLAP_JUDGE = 4.0f;
	
	const Float2 SPEED_MAX = { 2.0f, 10.0f };
	const float DASH_SPEED_MAX = 3.0f;

	const int BASE_STOCK = 3;
	const int STOCK_MAX = 99;

	const float SQUASH_BOUNCE_POWER = 4.5f;

	bool isGrounded;//地面にいるかどうか
	bool isJumping;

	Float2 prevPos;
	int state;

	bool isFacingRight;
	bool isCrouching;
	bool isTryingToStand;
	float standPushDir;
	int fireCooldown;

	int score;
	int stock;

	bool isStar;
	int starTimer;
	int fireballCount;
	enum PlayerState
	{
		SMALL,
		SUPER,
		FIRE,
	};

	TileManager* tileManager = nullptr;
	ObjectManager* objectManager = nullptr;

	void Input();
	void MoveX();
	void MoveY();
	void Jump();
	void ApplyGravity();
	void CheckCollisionX();
	void CheckCollisionY();
	bool CheckGround();

	void UpdatePlayerSize();
	bool CheckCanStand();
	void UpdateStandPush();
};

