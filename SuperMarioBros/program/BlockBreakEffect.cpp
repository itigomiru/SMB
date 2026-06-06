#include "BlockBreakEffect.h"

BrockBreakEffect::BrockBreakEffect(float x, float y) : Effect(x, y) {
    // 4方向の初速を定義
    float vxs[] = { -SPEEDX, SPEEDX, -SPEEDX, SPEEDX };
    float vys[] = { TOPSPEEDY, TOPSPEEDY, BOTTOMSPEEDY, BOTTOMSPEEDY };

    for (int i = 0; i < 4; i++) {
        particles[i] = { x, y, vxs[i], vys[i] };
    }
}

void BrockBreakEffect::Update() {
    for (int i = 0; i < 4; i++) {
        particles[i].vy += GRAVITY;
        particles[i].x += particles[i].vx;
        particles[i].y += particles[i].vy;
    }
    // 全ての破片が画面外へ出たら消滅
    if (particles[0].y > 600) isDead = true;
}

void BrockBreakEffect::Render(float cameraX) {
    for (int i = 0; i < 4; i++) {
        int drawX = static_cast<int>(particles[i].x - cameraX);
        int drawY = static_cast<int>(particles[i].y);
		int srcX = i * SIZE; 
		DrawRectGraph(drawX, drawY, srcX, 0, SIZE, SIZE, ImageManager::GetInstance().GetImage(IMAGE_BLOCK_BREAK), true);
    }
}
