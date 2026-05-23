#pragma once
#include "Object.h"

class Goomba : public Object
{
public:
	Goomba();
	void Update() override;
	void Render(float cameraX) override;


private:
	const float HEIGHT = 16.0f;
	const float WIDTH = 16.0f;
};
