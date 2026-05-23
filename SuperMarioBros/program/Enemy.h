#pragma once
#include "Object.h"
class Enemy : Object
{
protected:
	bool isGrounded;
	int state;
public:
	Enemy() { objectType = OT_ENEMY; renderLayer = RL_ENEMY; isGrounded = false; state = 0; };
	virtual void Move() = 0;
	virtual void ApplyGravity() = 0;
};