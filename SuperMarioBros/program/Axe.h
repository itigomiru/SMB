#pragma once
#include "Object.h"
class Axe : public Object
{
private:
    int animationCounter;
    int animWaitCounter;

    static const int AXE_FRAME_W = 16;
    static const int AXE_FRAME_H = 16;
    static const int AXE_ANIM_SPEED = 8;
    static const int AXE_ANIM_FRAMES = 3;
    static const int AXE_ANIM_WAIT_TIME = 20;

public:
    Axe();

    void Update(float cameraX) override;
    void Render(float cameraX) override;

    
};