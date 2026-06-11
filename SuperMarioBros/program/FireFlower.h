#pragma once
#include "Item.h"
class FireFlower : public Item
{
private:
	int animationCounter = 0;       
	int animWaitCounter = 0;        

	const int ANIM_SPEED = 4;
	const int ANIM_FRAMES = 4;
public:
	FireFlower(float tileX, float tileY, int type);
	void Update(float cameraX) override;
	void Render(float cameraX) override;

};