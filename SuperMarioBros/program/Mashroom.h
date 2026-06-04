#pragma once
#include "Item.h"
class Mashroom : public Item
{
public:
	Mashroom(float tileX, float tileY,int type);
	void Update(float cameraX) override;
	void Render(float cameraX) override;
	int mashType;
	enum MASH_TYPE
	{
		MT_SUPER,
		MT_1UP,
	};
	void CheckCollisionX();
	void CheckCollisionY();
};