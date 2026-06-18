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

    void StartFlagMove();
    bool IsFlagEnd() const { return isFlagEnd; }

private:
    bool isFlagMoving;
    bool isFlagEnd;

    static constexpr float FLAG_DOWN_SPEED = 1.0f;
    static constexpr float FLAG_END_Y = 176.0f;
};