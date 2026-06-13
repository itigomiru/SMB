#pragma once
#include "Object.h"
class Axe : public Object
{
private:
    int animeFrame;
    int animeTimer;

    static const int AXE_FRAME_W = 16;
    static const int AXE_FRAME_H = 16;
    static const int AXE_FRAME_MAX = 3;
    static const int AXE_ANIME_INTERVAL = 10;

public:
    Axe();

    void Update(float cameraX) override;
    void Render(float cameraX) override;

    
};