#include "CoinEffect.h"
#include "SceneManager.h"

void CoinEffect::Update() {
    // 速度を更新
    speedY += GRAVITY;
    
    // 位置を更新
    y += speedY;

    timer++;

    if (speedY > 0 && y >= startY - TILE_SIZE) {
        isDead = true;
    }
}

void CoinEffect::Render(float cameraX) {
    int drawX = static_cast<int>(x) - static_cast<int>(cameraX);
    int drawY = static_cast<int>(y);
    int chipW = 8;
	int srcX = timer  / 2 % 4 * chipW; 
    // コインを描画 (黄色の円などで代用)
	DrawRectGraph(drawX, drawY, srcX, 0, 8, 16, ImageManager::GetInstance().GetImage(IMAGE_COIN), true);
    DrawFormatString(drawX, drawY - 20, GetColor(255, 255, 255), "Coin");
}