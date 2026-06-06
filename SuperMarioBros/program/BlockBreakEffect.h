#pragma once
#include "Effect.h"
#include <vector>

class BrockBreakEffect : public Effect {
private:
    struct Particle {
        float x, y, vx, vy;
    };
    Particle particles[4];
    const float GRAVITY = 0.4f;
	const float SPEEDX = 1.5f;
	const float TOPSPEEDY = -6.0f;
	const float BOTTOMSPEEDY = -3.0f;

	const int SIZE = 8; // 破片のサイズ
public:
    BrockBreakEffect(float x, float y);

    void Update() override;

    void Render(float cameraX) override;
};