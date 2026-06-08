#include "KoopaTroopaController.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "EnemyDefeatedEffect.h"
#include "Main.h"

KoopaTroopa::KoopaTroopa()
{
    pos = { 100.0f, 190.0f };
    prevPos = pos;
    objectType = OT_ENEMY;
    speed = { -SPEED.x, 0.0f };
    size = { WIDTH, HEIGHT };

    renderLayer = RL_ENEMY;
    isDead = false;
    isGrounded = false;
    state = 0;
    canSquashed = true;
    canDamage = true;
    koopaTroopaState = STATE_WALK;
    wakeUpTimer = 0;
	shakeOffset = { 0.0f, 0.0f };
}

void KoopaTroopa::Update(float cameraX)
{
    if (isDead)
    {
        return;
    }
    CheckOutOfScreen(cameraX);

    if (koopaTroopaState == STATE_SHELL_STOP || koopaTroopaState == STATE_SHELL_WAKEUP)
    {
        wakeUpTimer--;
        canDamage = false;
        shakeOffset = { 0.0f, 0.0f };

        if (wakeUpTimer <= 0)
        {
            koopaTroopaState = STATE_WALK;
            canSquashed = true;
            canDamage = true;
            speed.x = -SPEED.x;
			wakeUpTimer = 0;

			size.h = HEIGHT;
			pos.y -= (HEIGHT - SHELL_HEIGHT);
        }
        else if (wakeUpTimer <= SHELL_START_TIME)
        {
			koopaTroopaState = STATE_SHELL_WAKEUP;

            if (wakeUpTimer % 2 == 0) shakeOffset.x = 1.0f;
			else                      shakeOffset.x = -1.0f;
        }
        return;
    }

    if (koopaTroopaState == STATE_SHELL_ROLL)
    {
        canDamage = true;
    }

    isGrounded = CheckGround();
    prevPos = pos;
    Move();
    ApplyGravity();
    CheckCollisionX();
    CheckCollisionY();

}

void KoopaTroopa::Move()
{
    pos.x += speed.x;
    CheckCollisionX();
    pos.y += speed.y;
    CheckCollisionY();
}

void KoopaTroopa::OnSquashed()
{
    if (koopaTroopaState == STATE_WALK)
    {
        koopaTroopaState = STATE_SHELL_STOP;
        wakeUpTimer = WAKEUP_TIME;
        speed = { 0.0f, 0.0f };
        size.h = SHELL_HEIGHT;
		pos.y += (HEIGHT - SHELL_HEIGHT); 
    }
    else if (koopaTroopaState == STATE_SHELL_STOP || koopaTroopaState == STATE_SHELL_WAKEUP)
    {
        koopaTroopaState = STATE_SHELL_ROLL;
		canSquashed = true;
    }
    else if (koopaTroopaState == STATE_SHELL_ROLL)
    {
        koopaTroopaState = STATE_SHELL_STOP;
		objectType = OT_ENEMY;
		wakeUpTimer = WAKEUP_TIME;
        speed = { 0.0f, 0.0f };
		size.h = SHELL_HEIGHT;
    }
}

void KoopaTroopa::OnKicked(float marioX)
{
	koopaTroopaState = STATE_SHELL_ROLL;
	objectType = OT_SHELL;
    canSquashed = true;

    if (marioX < pos.x)
    {
        speed.x = SHELL_SPEED;
    }
    else
    {
		speed.x = -SHELL_SPEED;
    }

}

void KoopaTroopa::ApplyGravity()
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

void KoopaTroopa::CheckCollisionX()
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

void KoopaTroopa::CheckCollisionY()
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

bool KoopaTroopa::CheckGround()
{
    int px = static_cast<int>(pos.x);
    int py = static_cast<int>(pos.y);
    int left = px / TILE_SIZE;
    int right = (px + size.w - 1) / TILE_SIZE;
    int bottom = (py + size.h) / TILE_SIZE; // 足元1ピクセル下をチェック

    return tileManager->IsSolid(left, bottom) || tileManager->IsSolid(right, bottom);
}

// 描画関数
void KoopaTroopa::Render(float cameraX)
{
    int drawX = (static_cast<int>(pos.x) - static_cast<int>(cameraX));
    int drawY = static_cast<int>(pos.y);

    int shakeDrawX = drawX + static_cast<int>(shakeOffset.x);

    int srcX = 0;
    int srcY = 0;

	int color = GetColor(255, 255, 255); 
    switch (koopaTroopaState)
    {       
    case STATE_WALK:
        {
            int walkFrame = (GetNowCount() / 150) % 2;
            srcX = walkFrame * static_cast<int>(WIDTH);
			srcY = 0;
        }
        break;

    case STATE_SHELL_STOP:
    case STATE_SHELL_ROLL:   
            srcX = 2 * static_cast<int>(WIDTH);
			srcY = HEIGHT - SHELL_HEIGHT;
            break;

    case STATE_SHELL_WAKEUP:
    {
        int wakeFrame = (wakeUpTimer / 4) % 2;
        srcX = (2 + wakeFrame) * static_cast<int>(WIDTH);
		srcY = HEIGHT - SHELL_HEIGHT;
    }
            break;
    }
    int imgHandle = ImageManager::GetInstance().GetImage(IMAGE_ENEMY_KOOPATROOPA);

	DrawRectGraph(shakeDrawX, drawY, srcX, srcY, static_cast<int>(WIDTH), static_cast<int>(size.h), imgHandle, TRUE, (speed.x > 0.0f));

}

void KoopaTroopa::SetPosition(float x, float y)
{
    pos.x = x;
    pos.y = y;
    //prevPos = pos;
}

void KoopaTroopa::SetTileManager(TileManager* tm)
{
    tileManager = tm;
}

void KoopaTroopa::Death(bool isRight)
{
    isDead = true;
	EffectManager::GetInstance().AddEffect(std::make_unique<EnemyDefeatedEffect>(pos.x, pos.y, ET_KOOPATROOPA, isRight));
}