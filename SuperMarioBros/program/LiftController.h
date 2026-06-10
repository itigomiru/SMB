#pragma once

#include "Object.h"

class Lift : public Object
{
private:
	Float2 startPos;

	float moveDistance;
	
	float moveX;

	static const int LIFT_W = 32;
	static const int LIFT_H = 8;

	const float LIFT_SPEED = 1.0f;
public:

	Lift(float x, float y, float moveDistance);

	void Update(float cameraX) override;
	void Render(float cameraX) override;

	float GetMoveX() const { return moveX; }
};
