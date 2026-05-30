#pragma once
#include "Object.h"

class TileManager;
class ObjectManager;

class Fireball : public Object
{
public:
	Fireball(Float2 pos, bool isFacingRight, TileManager* tm, ObjectManager* om);
	void Update(float cameraX) override;
	void Render(float cameraX) override;

private:
	void ApplyGravity();
	void CheckCollisionX();
	void CheckCollisionY();
	void CheckCollisionWithEnemies();
	void MoveX();
	void MoveY();

	bool CheckInScreen(float cameraX);

	TileManager* tileManager = nullptr;
	ObjectManager* objectManager = nullptr;
	const float MOVE_SPEED = 4.0f;
	const float JUMP_POWER = 5.0f; 
	const Float2 VEL_MAX = { 5.0f, 10.0f };
	int bounceCount = 0;
	const int MAX_BOUNCES = 60;
};
