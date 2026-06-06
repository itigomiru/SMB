#pragma once
#include "Effect.h"
#include "SceneManager.h"

class CoinEffect : public Effect {
private:
    float startY;     // 出現時のY座標
    int timer;      // 経過時間管理用
    float speedY;     // 縦方向の速度
    const float GRAVITY = 0.5f; // 重力
	

public:
    CoinEffect(float x, float y) : Effect(x, y) {
        startY = y - TILE_SIZE;
        timer = 0;
        speedY = -8.0f; // 最初に上に跳ね上がる初速
    }

    void Update() override;
    void Render(float cameraX) override;
};