#include "ScoreEffect.h"
#include "ImageManager.h"
#include "PlayerData.h"
#include "DxLib.h" 

ScoreEffect::ScoreEffect(Float2 position, int score)
    : Effect(position.x, position.y - 10)
    , scoreValue(score)
    , timer(0)
{
    speed.x = 0.0f;
    speed.y = -1.0f;
	PlayerData::GetInstance().AddScore(REAL_SCORE[score]);
}

void ScoreEffect::Update()
{
    timer++;

    x += speed.x;
    y += speed.y;


    if (timer >= LIFE_TIME)
    {
        isDead = true;
    }
}
void ScoreEffect::Render(float cameraX)
{
	int drawX = static_cast<int>(x) - static_cast<int>(cameraX);
	int drawY = static_cast<int>(y);

	int srcX = scoreValue * 16;

	DrawRectGraph(drawX, drawY, srcX, 0, 16, 8, ImageManager::GetInstance().GetImage(IMAGE_SCORE), true);
}