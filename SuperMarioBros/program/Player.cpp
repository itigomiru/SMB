#include "Player.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Main.h"

Player::Player() {
    pos = { 20.0f, 200.0f };
	prevPos = pos;
	objectType = PLAYER;
    vel = { 0.0f, 0.0f };
    size = { WIDTH, CHIBI_H };


    isDead = false;
    isGrounded = false;
}

void Player::Update() {
    // ★復活：毎フレーム最初に足元を確認する（これが無いと上下にガタつきます）
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
    constexpr float MOVE_ACCEL = 0.1f;
    constexpr float FRICTION = 0.1f;

    if (CheckHitKey(KEY_INPUT_A))
    {
        vel.x -= MOVE_ACCEL;
    }
    else if (CheckHitKey(KEY_INPUT_D))
    {
        vel.x += MOVE_ACCEL;
    }
    else
    {
        // 摩擦
        if (vel.x > 0.0f)
        {
            vel.x -= FRICTION;
            if (vel.x < 0.0f) vel.x = 0.0f;
        }
        else if (vel.x < 0.0f)
        {
            vel.x += FRICTION;
            if (vel.x > 0.0f) vel.x = 0.0f;
        }
    }

    // 最大速度制限
    if (vel.x > VEL_MAX.x) vel.x = VEL_MAX.x;
    else if (vel.x < -VEL_MAX.x) vel.x = -VEL_MAX.x;
}

void Player::Jump() {
    constexpr float JUMP_POWER = 7.0f;

    if (PushHitKey(KEY_INPUT_SPACE) && isGrounded)
    {
        vel.y = -JUMP_POWER;
        isGrounded = false; // ジャンプした瞬間は空中にする
    }
}

void Player::ApplyGravity() {
    if (!isGrounded)
    {
        vel.y += SceneManager::GetInstance().GRAVITY;

        if (vel.y > VEL_MAX.y)
        {
            vel.y = VEL_MAX.y;
        }
    }
    else
    {
        vel.y = 0.0f;
    }
}

void Player::MoveX() {
    pos.x += vel.x;

    // 左端制限
    if (pos.x < 0.0f)
    {
        pos.x = 0.0f;
        vel.x = 0.0f;
    }
}

void Player::MoveY() {
    pos.y += vel.y;
}

void Player::CheckCollisionX() {
    int px = static_cast<int>(pos.x);
    int py = static_cast<int>(pos.y);
    int top = py / TILE_SIZE;
    int bottom = (py + size.h - 1) / TILE_SIZE;

    // 右移動
    if (vel.x > 0.0f)
    {
        int right = (px + size.w) / TILE_SIZE;
        if (tileManager->IsSolid(right, top) || tileManager->IsSolid(right, bottom))
        {
            pos.x = static_cast<float>(right * TILE_SIZE - size.w);
            vel.x = 0.0f;
        }
    }
    // 左移動
    else if (vel.x < 0.0f)
    {
        int left = px / TILE_SIZE;
        if (tileManager->IsSolid(left, top) || tileManager->IsSolid(left, bottom))
        {
            pos.x = static_cast<float>((left + 1) * TILE_SIZE);
            vel.x = 0.0f;
        }
    }
}

void Player::CheckCollisionY() {
    int px = static_cast<int>(pos.x);
    int py = static_cast<int>(pos.y);
    int left = px / TILE_SIZE;
    int right = (px + size.w - 1) / TILE_SIZE;

    // 下方向
    if (vel.y > 0.0f)
    {
        int bottom = (py + size.h - 1) / TILE_SIZE;
        if (tileManager->IsSolid(left, bottom) || tileManager->IsSolid(right, bottom))
        {
            pos.y = static_cast<float>(bottom * TILE_SIZE - size.h);
            vel.y = 0.0f;
            isGrounded = true;
        }
    }
    // 上方向
    else if (vel.y < 0.0f)
    {
        int top = py / TILE_SIZE;
        if (tileManager->IsSolid(left, top) || tileManager->IsSolid(right, top))
        {
            pos.y = static_cast<float>((top + 1) * TILE_SIZE);
            vel.y = 0.0f;
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
    int drawX = (static_cast<int>(pos.x) - static_cast<int>(cameraX)) * 3;
    int drawY = static_cast<int>(pos.y) * 3;

    DrawBox(drawX,drawY,drawX + size.w * 3,drawY + size.h * 3,GetColor(0, 255, 0),true);

    DrawFormatString(0, 0, 0xFFFFFF, "Player pos: (%.2f, %.2f)", pos.x, pos.y);
    DrawFormatString(0, 16, 0xFFFFFF, "isGrounded: (%d)", isGrounded);
}

void Player::SetTileManager(TileManager* tm) {
    tileManager = tm;
}