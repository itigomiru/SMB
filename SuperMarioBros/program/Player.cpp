#include "Player.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Main.h"

Player::Player() {
    pos = { 20.0f, 200.0f };
	prevPos = pos;
	objectType = OT_PLAYER;
    speed = { 0.0f, 0.0f };
    size = { WIDTH, CHIBI_H };

    renderLayer = RL_PLAYER;
    isDead = false;
    isGrounded = false;
}

void Player::Update() 
{
    isGrounded = CheckGround();

    Input();

    Jump();

    ApplyGravity();

    MoveX();
    CheckCollisionX();

    MoveY();
    CheckCollisionY();
}

void Player::Input() {


    if (CheckHitKey(KEY_INPUT_A))
    {
        speed.x -= MOVE_ACCEL;
    }
    else if (CheckHitKey(KEY_INPUT_D))
    {
        speed.x += MOVE_ACCEL;
    }
    else
    {
        // 摩擦
        if (speed.x > 0.0f)
        {
            speed.x -= FRICTION;
            if (speed.x < 0.0f) speed.x = 0.0f;
        }
        else if (speed.x < 0.0f)
        {
            speed.x += FRICTION;
            if (speed.x > 0.0f) speed.x = 0.0f;
        }
    }

    // 最大速度制限
    if (speed.x > VEL_MAX.x) speed.x = VEL_MAX.x;
    else if (speed.x < -VEL_MAX.x) speed.x = -VEL_MAX.x;
}

void Player::Jump() {

    if (PushHitKey(KEY_INPUT_SPACE) && isGrounded)
    {
        speed.y = -JUMP_POWER;
        isGrounded = false; // ジャンプした瞬間は空中にする
    }
}

void Player::ApplyGravity() {
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

void Player::MoveX() {
    pos.x += speed.x;

    // 左端制限
    if (pos.x < 0.0f)
    {
        pos.x = 0.0f;
        speed.x = 0.0f;
    }
}

void Player::MoveY() {
    pos.y += speed.y;
}

void Player::CheckCollisionX() {
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
            speed.x = 0.0f;
        }
    }
    // 左移動
    else if (speed.x < 0.0f)
    {
        int left = px / TILE_SIZE;
        if (tileManager->IsSolid(left, top) || tileManager->IsSolid(left, bottom))
        {
            pos.x = static_cast<float>((left + 1) * TILE_SIZE);
            speed.x = 0.0f;
        }
    }
}

void Player::CheckCollisionY() {
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

bool Player::CheckGround() {
    int px = static_cast<int>(pos.x);
    int py = static_cast<int>(pos.y);
    int left = px / TILE_SIZE;
    int right = (px + size.w - 1) / TILE_SIZE;
    int bottom = (py + size.h) / TILE_SIZE; // 足元1ピクセル下をチェック

    return tileManager->IsSolid(left, bottom) || tileManager->IsSolid(right, bottom);
}

void Player::Render(float cameraX) {
    int drawX = (static_cast<int>(pos.x) - static_cast<int>(cameraX));
    int drawY = static_cast<int>(pos.y) ;

    DrawBox(drawX,drawY,drawX + size.w ,drawY + size.h,GetColor(0, 255, 0),true);

    DrawFormatString(0, 0, 0xFFFFFF, "Player pos: (%.2f, %.2f)", pos.x, pos.y);
    DrawFormatString(0, 16, 0xFFFFFF, "isGrounded: (%d)", isGrounded);
}

void Player::SetTileManager(TileManager* tm) {
    tileManager = tm;
}