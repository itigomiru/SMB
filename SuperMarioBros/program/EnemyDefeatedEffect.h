#pragma once
#include "Effect.h"
#include "Enemy.h" 

class EnemyDefeatedEffect : public Effect {
private:
    int enemyType;
    float speedX;       
    float speedY;       
    float angle = 0.0f; 

    const float GRAVITY = 0.4f;       
    const float INITIAL_JUMP = -7.0f; 
    const float HORIZONTAL_SPEED = 3.0f; 

public:
    EnemyDefeatedEffect(float startX, float startY, int type, bool toRight);

    void Update() override;
    void Render(float cameraX) override;
};