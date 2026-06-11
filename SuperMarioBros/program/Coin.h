#pragma once
#pragma once
#include "Item.h"
class Coin : public Item
{
private:
	int animationCounter = 0;
	const int ANIM_SPEED = 10;
	const int ANIM_FRAMES = 3;

	bool isWait = false;
	int animWaitCounter = 0;
	const int ANIM_WAIT_TIME = 20;
public:
	Coin(float x, float y);
	void Update(float cameraX) override;
	void Render(float cameraX) override;

};