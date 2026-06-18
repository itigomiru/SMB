#include "GoombaController.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include"EffectManager.h"
#include"EnemyDefeatedEffect.h"
#include "ScoreEffect.h"
#include "Main.h"

Goomba::Goomba()
{
	pos = { 100.0f, 200.0f };
	hitBoxPos = pos;
	prevPos = pos;
	objectType = OT_ENEMY;
	speed = { -SPEED.x, 0.0f };
	size = { WIDTH, HEIGHT };
	hitBoxSize = size;

	renderLayer = RL_ENEMY;
	isDead = false;
	isGrounded = false;
	state = 0;
	canSquashed = true;
	canDamage = true;
	goombaState = STATE_WALK;
    squashTimer = 0;
}

void Goomba::Update(float cameraX)
{
    if (isDead)
    {
        return;
    }

	CheckOutOfScreen(cameraX);

    if (goombaState == STATE_SQUASHED)
    {
        squashTimer--;
		canDamage = false;
        if (squashTimer <= 0)
        {
            isDead = true; 
        }
        return; 
    }

	isGrounded = CheckGround();
	prevPos = pos;
	Move();
	ApplyGravity();
	hitBoxPos = pos;
	hitBoxSize = size;
	CheckCollisionX();
	CheckCollisionY();
    hitBoxPos = pos;
    hitBoxSize = size;
    animationCounter = (animationCounter + 1) % (ANIM_SPEED * ANIM_FRAMES);

}

void Goomba::Move()
{
	pos.x += speed.x;
	CheckCollisionX();
	pos.y += speed.y;
	CheckCollisionY();
}

void Goomba::OnSquashed()
{
	if (goombaState == STATE_WALK)
	{
        goombaState = STATE_SQUASHED;
        canSquashed = false;
        squashTimer = 30;
        speed = { 0.0f, 0.0f };
	}
}

void Goomba::ApplyGravity()
{
    if (!isGrounded)
    {
        speed.y += SceneManager::GetInstance().GRAVITY;

        if (speed.y > SPEED.y)
        {
            speed.y = SPEED.y;
        }
    }
    else
    {
        speed.y = 0.0f;
    }
}

void Goomba::CheckCollisionX()
{
    int px = static_cast<int>(pos.x);
    int py = static_cast<int>(pos.y);
    int top = py / TILE_SIZE;
    int bottom = (py + size.h - 1) / TILE_SIZE;

    // 右移動
    if (speed.x > 0.0f)
    {
        int right = (px + size.w) / TILE_SIZE;
        if (tileManager->IsSolid(right, top) || tileManager->IsSolid(right, bottom))
        {
            pos.x = static_cast<float>(right * TILE_SIZE - size.w);
            speed.x *= -1.0f;
        }
    }
    // 左移動
    else if (speed.x < 0.0f)
    {
        int left = px / TILE_SIZE;
        if (tileManager->IsSolid(left, top) || tileManager->IsSolid(left, bottom))
        {
            pos.x = static_cast<float>((left + 1) * TILE_SIZE);
            speed.x *= -1.0f;
        }
    }
}

void Goomba::CheckCollisionY()
{
    int px = static_cast<int>(pos.x);
    int py = static_cast<int>(pos.y);
    int left = px / TILE_SIZE;
    int right = (px + size.w - 1) / TILE_SIZE;

    // 下方向
    if (speed.y > 0.0f)
    {
        int bottom = (py + size.h - 1) / TILE_SIZE;
        if (tileManager->IsSolid(left, bottom) || tileManager->IsSolid(right, bottom))
        {
            pos.y = static_cast<float>(bottom * TILE_SIZE - size.h);
            speed.y = 0.0f;
            isGrounded = true;
        }
    }
    // 上方向
    else if (speed.y < 0.0f)
    {
        int top = py / TILE_SIZE;
        if (tileManager->IsSolid(left, top) || tileManager->IsSolid(right, top))
        {
            pos.y = static_cast<float>((top + 1) * TILE_SIZE);
            speed.y = 0.0f;
        }
    }
}

bool Goomba::CheckGround()
{
	int px = static_cast<int>(pos.x);
	int py = static_cast<int>(pos.y);
	int left = px / TILE_SIZE;
	int right = (px + size.w - 1) / TILE_SIZE;
	int bottom = (py + size.h) / TILE_SIZE; // 足元1ピクセル下をチェック

	return tileManager->IsSolid(left, bottom) || tileManager->IsSolid(right, bottom);
}

void Goomba::Render(float cameraX)
{
    if (isDead) return;

    int drawX = (static_cast<int>(pos.x) - static_cast<int>(cameraX));
    int drawY = static_cast<int>(pos.y);

    int srcX = 0;
    int srcY = 0;

	switch(goombaState)
		{
			case STATE_SQUASHED:
                srcX = 2 * size.w;
			break;
			
			default:
                int currentFrame = animationCounter / ANIM_SPEED;
                srcX = currentFrame * size.w;
			break;
		}

    int imgHandle = ImageManager::GetInstance().GetImage(IMAGE_ENEMY_GOOMBA);

    DrawRectGraph(drawX, drawY, srcX, srcY, size.w, size.h, imgHandle, TRUE, FALSE);


}

void Goomba::SetPosition(float x, float y)
{
	pos.x = x;
	pos.y = y;
	//prevPos = pos;
}

void Goomba::SetTileManager(TileManager* tm)
{
	tileManager = tm;
}

void Goomba::Death(bool isRight,int score)
{
	isDead = true;
	EffectManager::GetInstance().AddEffect(std::make_unique<EnemyDefeatedEffect>(pos.x, pos.y, ET_GOOMBA, isRight));
	EffectManager::GetInstance().AddEffect(std::make_unique<ScoreEffect>(pos, score));
}