#pragma once
#include "Object.h"

class TileManager;
class ObjectManager;

class Player : public Object
{
public:
	Player();
	void Update(float cameraX) override;
	void Render(float cameraX) override;

	void SetTileManager(TileManager* tm);
	void SetObjectManager(ObjectManager* om);
	void GetSuperMashroom();
	void GetFireFlower();
private:
	const float SMALL_H = 16.0f;
	const float SUPER_H = 32.0f;
	const float WIDTH = 16.0f;
	const float MOVE_ACCEL = 0.1f;	//加速度
	const float FRICTION = 0.2f;	//摩擦(キーを入れない時の減速度)
	const float JUMP_POWER = 7.0f;
	const int FIRE_COOLDOWN_TIME = 5;
	const int FIREBALL_MAX = 2;


	const Float2 VEL_MAX = { 5.0f, 10.0f };
	const float VEL_MIN = 0.05f;


	bool isGrounded;//地面にいるかどうか

	Float2 prevPos;
	int state;

	bool isFacingRight;
	bool isCrouching;
	bool isTryingToStand;
	float standPushDir;
	int fireCooldown;


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

