#pragma once
#include "Enemy.h"
#include "Object.h"

class TileManager;

class Goomba : public Enemy
{
	public:
	Goomba();
	void Update() override;
	void Render(float cameraX) override;
	void Move() override;
	void ApplyGravity() override;

	void SetPosition(float x, float y);
	void SetTileManager(TileManager* tm);

	void OnSquashed();

private:
	enum GoombaState
	{
		STATE_WALK,
		STATE_SQUASHED,
	};

	GoombaState goombaState;
	int squashTimer;

	const float HEIGHT = 16.0f;
	const float WIDTH = 16.0f;

	const Float2 VEL_MAX = { 5.0f, 10.0f };
	Float2 prevPos;

	TileManager* tileManager = nullptr;

	void CheckCollisionX();
	void CheckCollisionY();
	bool CheckGround();
};
