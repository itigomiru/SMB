#include "EnemyDefeatedEffect.h"
#include "ImageManager.h"
#include  "SoundManager.h"
#include "Enemy.h"

EnemyDefeatedEffect::EnemyDefeatedEffect(float startX, float startY, int type, bool toRight)
	: Effect(startX, startY), enemyType(type)
{
	// 1. 最初に一瞬浮き上がらせるための上向き速度
	speedY = INITIAL_JUMP;

	// 2. 左右どちらに 吹っ飛ぶか
	speedX = toRight ? HORIZONTAL_SPEED : -HORIZONTAL_SPEED;
	SoundManager::GetInstance().PlaySE(SoundManager::SE_KICK);
}

void EnemyDefeatedEffect::Update() {
	// 座標の更新（放物線運動）
	x += speedX;
	speedY += GRAVITY; // 下方向へ加速（重力）
	y += speedY;



	// 画面外（例えば y 座標が 600 以上など）に落ちたら自動消滅
	// ※SCREEN_H などの定数があればそれに書き換えてください
	if (y > 600.0f) {
		isDead = true;
	}
}

void EnemyDefeatedEffect::Render(float cameraX) {
	if (isDead) return;

	int drawX = static_cast<int>(x) - static_cast<int>(cameraX);
	int drawY = static_cast<int>(y);

	// 敵の種類に応じて描画する画像（ImageManagerのキー）を切り替える
	int imageID = 0;
	int srcX = 0;
	int sizeW = 16;
	int sizeH = 16;
	switch (enemyType) {
	case Enemy::ET_GOOMBA:
		imageID = IMAGE_ENEMY_GOOMBA;
		break;
	case Enemy::ET_KOOPATROOPA:
		imageID = IMAGE_ENEMY_KOOPATROOPA;
		srcX = 32;
		sizeH = 24;
		break;
	case Enemy::ET_BOWSER:
		imageID = IMAGE_ENEMY_BOWSER_WALK;
		srcX = 0;
		sizeW = 32;
		sizeH = 32;
		break;
	default:        imageID = IMAGE_ENEMY_GOOMBA; break;
	}

	int imgHandle = ImageManager::GetInstance().GetImage(imageID);


	DrawRectGraph(drawX, drawY, srcX, 0, sizeW, sizeH, imgHandle, true, (speedX < 0.0f), true);
}