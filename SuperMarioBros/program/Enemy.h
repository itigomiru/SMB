#pragma once
#include "Object.h"
class Enemy : public Object
{
protected:
	bool isGrounded;
	int state;
public:
	virtual void Update(float cameraX) override {};
	bool canSquashed;
	Enemy() 
	{
		objectType = OT_ENEMY; 
		renderLayer = RL_ENEMY; 
		isGrounded = false; 
		state = 0;
		canSquashed = true;
	};
	virtual void Move() = 0;
	virtual void ApplyGravity() = 0;
};