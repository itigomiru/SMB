#pragma once
#include "Object.h"
class Item : Object
{
	public:
	Item() { objectType = OT_ITEM; renderLayer = RL_UNDER_TILE; };
	void virtual Update() = 0;
	void virtual Render(float cameraX) = 0;
};
