#include "GoombaController.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Main.h"

Goomba::Goomba()
{
	pos = { 100.0f, 200.0f };
	prevPos = pos;
	objectType = OT_ENEMY;
	speed = { -1, 0.0f };
	size = { WIDTH, HEIGHT };

	renderLayer = RL_ENEMY;
	isDead = false;
	isGrounded = false;
	state = 0;
	canSquashed = true;

	goombaState = STATE_WALK;
    squashTimer = 0;
}

void Goomba::Update()
{
    if (isDead)
    {
        return;
    }

    if (goombaState == STATE_SQUASHED)
    {
        squashTimer--;
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
	CheckCollisionX();
	CheckCollisionY();

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

        if (speed.y > VEL_MAX.y)
        {
            speed.y = VEL_MAX.y;
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
    int drawX = (static_cast<int>(pos.x) - static_cast<int>(cameraX));
    int drawY = static_cast<int>(pos.y);

    if (goombaState == STATE_SQUASHED)
    {
        DrawBox(drawX, drawY, drawX + size.w, drawY + size.h, GetColor(255, 255, 0), true);
    }
    else
    {
        DrawBox(drawX, drawY, drawX + size.w, drawY + size.h, GetColor(0, 0, 255), true);
    }
    DrawFormatString(0, 0, 0xFFFFFF, "Goomba pos: (%.2f, %.2f)", pos.x, pos.y);


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

