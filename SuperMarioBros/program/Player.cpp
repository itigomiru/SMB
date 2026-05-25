#include "Player.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Main.h"


Player::Player()
{
	pos = { 20.0f, 200.0f };
	prevPos = pos;

	objectType = OT_PLAYER;

	speed = { 0.0f, 0.0f };

	size =
	{
		WIDTH,
		SMALL_H
	};

	state = SMALL;

	renderLayer = RL_PLAYER;

	isFacingRight = true;
	isDead = false;
	isGrounded = false;
	isCrouching = false;
}


void Player::Update()
{
	prevPos = pos;
	isGrounded = CheckGround();

#if 1
	if (PushHitKey(KEY_INPUT_0))
	{
		GetSuperMashroom();
	}
#endif

	Input();

	UpdatePlayerSize();
	UpdateStandPush();

	Jump();

	ApplyGravity();

	MoveX();
	CheckCollisionX();

	MoveY();
	CheckCollisionY();
}


void Player::Input()
{
	// しゃがみ
	if (CheckHitKey(KEY_INPUT_S) &&
		state != SMALL)
	{
		if (!isCrouching)
		{
			isCrouching = true;
			isTryingToStand = false;
			// 足固定で縮む
			pos.y += (SUPER_H - SMALL_H);
		}
	}
	else
	{
		if (isCrouching)
		{
			if (CheckCanStand())
			{
				isCrouching = false;
				isTryingToStand = false;
				standPushDir = 0.0f;
				pos.y -= (SUPER_H - SMALL_H);
			}
			else
			{
				isTryingToStand = true;
			}
		}
	}
	// 横移動
	if (CheckHitKey(KEY_INPUT_A) && !isCrouching)
	{
		speed.x -= MOVE_ACCEL;
		isFacingRight = false;
	}
	else if
		(CheckHitKey(KEY_INPUT_D) && !isCrouching)
	{
		speed.x += MOVE_ACCEL;
		isFacingRight = true;
	}
	else
	{
		// 摩擦
		if (speed.x > 0.0f)
		{
			speed.x -= FRICTION;

			if (speed.x < 0.0f)
			{
				speed.x = 0.0f;
			}
		}
		else if (speed.x < 0.0f)
		{
			speed.x += FRICTION;

			if (speed.x > 0.0f)
			{
				speed.x = 0.0f;
			}
		}
	}

	//=========================================================
	// 最大速度制限
	//=========================================================

	if (speed.x > VEL_MAX.x)
	{
		speed.x = VEL_MAX.x;
	}
	else if (speed.x < -VEL_MAX.x)
	{
		speed.x = -VEL_MAX.x;
	}
}

void Player::Jump()
{
	if (PushHitKey(KEY_INPUT_SPACE) &&
		isGrounded)
	{
		speed.y = -JUMP_POWER;


		isGrounded = false;
	}
}


void Player::ApplyGravity()
{
	if (!isGrounded)
	{
		speed.y +=
			SceneManager::GetInstance().GRAVITY;

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

void Player::MoveX()
{
	pos.x += speed.x;


	// 左端制限
	if (pos.x < 0.0f)
	{
		pos.x = 0.0f;

		speed.x = 0.0f;
	}
}


void Player::MoveY()
{
	pos.y += speed.y;
}

void Player::CheckCollisionX()
{
	int px =
		static_cast<int>(pos.x);

	int py =
		static_cast<int>(pos.y);

	int top =
		py / TILE_SIZE;

	int bottom =
		(py + size.h - 1)
		/ TILE_SIZE;

	//=========================================================
	// 右移動
	//=========================================================

	if (speed.x > 0.0f)
	{
		int right =
			(px + size.w)
			/ TILE_SIZE;

		if (tileManager->IsSolid(right, top) ||
			tileManager->IsSolid(right, bottom))
		{
			pos.x =
				static_cast<float>(
					right * TILE_SIZE - size.w);

			speed.x = 0.0f;
		}
	}

	//=========================================================
	// 左移動
	//=========================================================

	else if (speed.x < 0.0f)
	{
		int left =
			px / TILE_SIZE;

		if (tileManager->IsSolid(left, top) ||
			tileManager->IsSolid(left, bottom))
		{
			pos.x =
				static_cast<float>(
					(left + 1) * TILE_SIZE);

			speed.x = 0.0f;
		}
	}
}

void Player::CheckCollisionY()
{
	int px =
		static_cast<int>(pos.x);

	int py =
		static_cast<int>(pos.y);

	int left =
		px / TILE_SIZE;

	int right =
		(px + size.w - 1)
		/ TILE_SIZE;

	//=========================================================
	// 下方向
	//=========================================================

	if (speed.y > 0.0f)
	{
		int bottom =
			(py + size.h - 1)
			/ TILE_SIZE;

		if (tileManager->IsSolid(left, bottom) ||
			tileManager->IsSolid(right, bottom))
		{
			pos.y =
				static_cast<float>(
					bottom * TILE_SIZE - size.h);

			speed.y = 0.0f;

			isGrounded = true;
		}
	}

	//=========================================================
	// 上方向
	//=========================================================

	else if (speed.y < 0.0f)
	{
		int top =
			py / TILE_SIZE;

		if (tileManager->IsSolid(left, top) ||
			tileManager->IsSolid(right, top))
		{
			pos.y =
				static_cast<float>(
					(top + 1) * TILE_SIZE);

			speed.y = 0.0f;
		}
	}
}

bool Player::CheckGround()
{
	int px =
		static_cast<int>(pos.x);

	int py =
		static_cast<int>(pos.y);

	int left =
		px / TILE_SIZE;

	int right =
		(px + size.w - 1)
		/ TILE_SIZE;

	int bottom =
		(py + size.h)
		/ TILE_SIZE;

	return
		tileManager->IsSolid(left, bottom) ||
		tileManager->IsSolid(right, bottom);
}

void Player::Render(float cameraX)
{
	int drawX = static_cast<int>(pos.x - cameraX);

	int drawY = static_cast<int>(pos.y);

	DrawBox(drawX,drawY,drawX + size.w,drawY + size.h,GetColor(0, 255, 0),true);

	DrawFormatString(0,5,0xFFFFFF,"Player pos:(%.2f %.2f)",pos.x,pos.y);

	DrawFormatString(0,16,0xFFFFFF,"isGrounded:%d",isGrounded);
	DrawFormatString(0,32,0xFFFFFF,"isCrouching:%d",isCrouching);
}

void Player::SetTileManager(TileManager* tm)
{
	tileManager = tm;
}



void Player::GetSuperMashroom()
{
	switch (state)
	{
	case SMALL:

		state = SUPER;

		pos.y -=
			(SUPER_H - SMALL_H);

		break;

	case SUPER:
		break;

	case FIRE:
		break;
	}
}

void Player::UpdatePlayerSize()
{
	if (state == SMALL)
	{
		size.h = SMALL_H;
	}
	else
	{
		if (isCrouching)
		{
			size.h = SMALL_H;
		}
		else
		{
			size.h = SUPER_H;
		}
	}
}

bool Player::CheckCanStand()
{
	int px = static_cast<int>(pos.x);

	int py = static_cast<int>(pos.y);

	int left = px / TILE_SIZE;

	int right = (px + size.w - 1) / TILE_SIZE;

	int checkY = py - (SUPER_H - SMALL_H);

	int top = checkY / TILE_SIZE;

	for (int x = left; x <= right; ++x)
	{
		if (tileManager->IsSolid(x, top))
		{
			return false;
		}
	}

	return true;
}



void Player::UpdateStandPush()
{
	if (!isTryingToStand)
	{
		return;
	}

	// 左右どっちへ押すか
	float push = isFacingRight ? 1.0f : -1.0f;

	// 仮移動
	pos.x += push;

	// 横壁チェック
	int px = static_cast<int>(pos.x);
	int py = static_cast<int>(pos.y);

	int top =py / TILE_SIZE;

	int bottom =(py + size.h - 1) / TILE_SIZE;

	//=====================================================
	// 右
	//=====================================================

	if (push > 0.0f)
	{
		int right =(px + size.w) / TILE_SIZE;

		if (tileManager->IsSolid(right, top) || tileManager->IsSolid(right, bottom))
		{
			pos.x -= push;
			return;
		}
	}

	//=====================================================
	// 左
	//=====================================================

	else
	{
		int left = px / TILE_SIZE;

		if (tileManager->IsSolid(left, top) || tileManager->IsSolid(left, bottom))
		{
			pos.x -= push;
			return;
		}
	}

	//=====================================================
	// 立てるなら復帰
	//=====================================================

	if (CheckCanStand())
	{
		isTryingToStand = false;

		isCrouching = false;

		pos.y -= (SUPER_H - SMALL_H);
	}
}

