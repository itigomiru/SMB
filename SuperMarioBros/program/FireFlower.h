#pragma once
#pragma once
#include "Item.h"
class FireFlower : public Item
{
public:
	FireFlower(float tileX, float tileY, int type);
	void Update(float cameraX) override;
	void Render(float cameraX) override;

};