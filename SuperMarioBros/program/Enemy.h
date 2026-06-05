#pragma once
#include "Object.h"
#include "SceneManager.h"
class Enemy : public Object
{
protected:
	bool isGrounded;
	int state;
	const int OUT_OF_SCREEN_MASS = 10;
	virtual void CheckOutOfScreen(float cameraX) {if (pos.x < cameraX - (OUT_OF_SCREEN_MASS * TILE_SIZE))isDead = true;	};
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
	virtual void Death() { }
	virtual void OnSquashed() {}
	virtual void Move() = 0;
	virtual void ApplyGravity() = 0;
};