#pragma once
#include "Item.h"

class Star : public Item
{
public:
    Star(float tileX, float tileY, int type);

    void Update(float cameraX) override;
	void Render(float cameraX) override;

private:
    const float MOVE_SPEED = 0.7f;       // 左右の移動速度
    const float BOUNCE_POWER = -4.0f;    // 跳ねる強さ



    Float2 prevPos;

    void CheckCollisionX();
    void CheckCollisionY();
};