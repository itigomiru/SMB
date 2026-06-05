#include "FireballEffect.h"

void FireballEffect::Update() {
    animTimer++;
    if (animTimer >= ANIM_SPEED) {
        animTimer = 0;
        currentFrame++;

        // 最後のコマを超えたら消滅フラグを立てる (EffectクラスのisDead)
        if (currentFrame >= FRAME_COUNT) {
            isDead = true;
        }
    }
}

void FireballEffect::Render(float cameraX) {
    if (isDead) return;

    int drawX = static_cast<int>(x) - static_cast<int>(cameraX);
    int drawY = static_cast<int>(y);

    int srcX = currentFrame * FRAME_WIDTH;
    int srcY = 0;

    // DrawRectGraph で切り出し描画
    DrawRectGraph(drawX, drawY,srcX, srcY,FRAME_WIDTH, FRAME_HEIGHT,ImageManager::GetInstance().GetImage(IMAGE_FIRE_BALL_EFFECT),true,false);
}