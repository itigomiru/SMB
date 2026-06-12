#pragma once
#include "Object.h"
class Goal : public Object
{
public:
    Goal();

    Float2 flagPos;

    void Update(float cameraX) override;
    void Render(float cameraX) override;

    int GetScore(float playerY);
};