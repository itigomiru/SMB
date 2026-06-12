#pragma once
#include "Object.h"
#include "Float2.h"

class Breath : public Object
{
public:
	Breath(bool isRight, Float2 position, float targetY, float moveSpeed);

	void Update(float cameraX) override;
	void Render(float cameraX) override;

private:
	bool isRight; // Œü‚«

	enum BreathState
	{
		BREATH_MOVE_TO_TARGET_Y,
		BREATH_FLY_STRAIGHT,
	};

	BreathState state;

	float targetY;

	static const int BREATH_W = 28; 
	static const int BREATH_H = 10;

	const float BREATH_Y_SPEED = 1.0f;
};