#pragma once
#include "Object.h"


class Player : public Object
{
	public:
	Player();
	void update() override;
	void render() override;
private:
	const float CHIBI_H = 16.0f;
	const float DEKA_H = 32.0f;
	const float WIDTH = 16.0f;

	const Float2 VEL_MAX = { 2.0f, 10.0f };
	Float2 prevPos;

	void Input();
	void Move();
	void Jump();
	void ApplyGravity();
	void CheckCollisionToTile();
};