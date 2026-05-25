#pragma once
#include "Object.h"

class TileManager;

class Player : public Object
{
	public:
	Player();
	void Update() override;
	void Render(float cameraX) override;

	void SetTileManager(TileManager* tm);
private:
	const float CHIBI_H = 16.0f;
	const float DEKA_H = 32.0f;
	const float WIDTH = 16.0f;
	const float MOVE_ACCEL = 0.1f;
	const float FRICTION = 0.1f;
	const float JUMP_POWER = 7.0f;


	const Float2 VEL_MAX = { 5.0f, 10.0f };
	const float VEL_MIN = 0.05f;
	bool isGrounded;//’n–Ê‚É‚¢‚é‚©‚Ç‚¤‚©
	Float2 prevPos;

	TileManager* tileManager = nullptr;

	void Input();
	void MoveX();
	void MoveY();
	void Jump();
	void ApplyGravity();
	void CheckCollisionX();
	void CheckCollisionY();
	bool CheckGround();
};