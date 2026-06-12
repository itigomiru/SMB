#pragma once
#include "Enemy.h"

class TileManager;
class ObjectManager;
class Player;

class Bowser : public Enemy
{
public:
	Bowser(float x, float y, float leftLimit, float rightLimit);

	void Update(float cameraX) override;
	void Render(float cameraX) override;

	void Move() override;
	void ApplyGravity() override;
	void OnSquashed() override;
	void Death(bool isRight, int score) override;

	int GetEnemyType() const override { return Enemy::ET_BOWSER; }
	void SetTileManager(TileManager* tm) { tileManager = tm; }
	void SetObjectManager(ObjectManager* om) { objectManager = om; }
	void SetPlayer(Player* p) { player = p; }
	void Damage();

private:
	TileManager* tileManager = nullptr;
	ObjectManager* objectManager = nullptr;
	Player* player = nullptr;

	bool hasBreath;
	int breathTimer;
	int breathCoolDown;
	static const int BREATH_COOLDOWN = 240;

	int hp;
	
	static const int MAX_HP = 5;
	static const int BOWSER_W = 32;
	static const int BOWSER_H = 32;
	const float SIZE_H_HALF = size.h / 2.0f;


	const float GRAVITY = 0.15f;
	const float FALL_SPEED_MAX = 6.0f;

	const float BOWSER_MOVE_SPEED = 0.5f;

	float moveLeftLimit;
	float moveRightLimit;
	
	bool isFacingRight;


	enum BowserAction
	{
		ACTION_MOVE_RIGHT,
		ACTION_MOVE_LEFT,
		ACTION_BREATH,
	};

	BowserAction action;
	int actionTimer;
	int jumpTimer;
	const float BOWSER_JUMP_POWER = 4.0f;
	bool hasJumped;

	void SelectAction();

	int animeFrame;
	int animeTimer;

	static const int BOWSER_FRAME_W = 32;
	static const int BOWSER_FRAME_H = 32;
	static const int BOWSER_ANIME_INTERVAL = 12;
	
};