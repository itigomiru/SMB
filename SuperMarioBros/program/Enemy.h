#pragma once
#include "Object.h"
#include "SceneManager.h"
class Enemy : public Object
{
protected:
	const int OUT_OF_SCREEN_MASS = 3; // 画面外に出るまでのマス数
	virtual void CheckOutOfScreen(float cameraX) { if (pos.x < cameraX - (OUT_OF_SCREEN_MASS * TILE_SIZE))isDead = true; };
	bool isGrounded;
	int state;
public:
	virtual void Update(float cameraX) override {};
	bool canSquashed;
	bool canDamage;
	Enemy()
	{
		objectType = OT_ENEMY;
		renderLayer = RL_ENEMY;
		isGrounded = false;
		state = 0;
		canSquashed = true;
		canDamage = true;
	};
	enum EnemyType
	{
		ET_GOOMBA,
		ET_KOOPATROOPA,
	};
	virtual void Death(bool isRight,int score) {}
	virtual void OnSquashed() {}
	virtual void Move() = 0;
	virtual void ApplyGravity() = 0;
	virtual int GetEnemyType() const = 0;
};