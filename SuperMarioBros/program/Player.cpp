#include "Player.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "Main.h"
#include "Fireball.h"
#include "ObjectManager.h"
#include "Hit.h"


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


void Player::Update(float cameraX)
{
	prevPos = pos;
	isGrounded = CheckGround();

#if 1
	if (PushHitKey(KEY_INPUT_0))
	{
		GetSuperMashroom();
	}
	if (PushHitKey(KEY_INPUT_9))
	{
		GetFireFlower();
	}
#endif

	if (fireCooldown > 0)
	{
		fireCooldown--;
	}

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
		if (isGrounded)
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
	}

	fireballCount = objectManager->GetFireballCount();
	if (PushHitKey(KEY_INPUT_Z) && state == FIRE && fireCooldown == 0 && fireballCount < FIREBALL_MAX)
	{
		Float2 fireballPos = pos;
		fireballPos.x += isFacingRight ? size.w : 0; 
		fireballPos.y += size.h / 4;
		auto fireball = std::make_unique<Fireball>(fireballPos, isFacingRight, tileManager, objectManager);
		objectManager->AddObject(std::move(fireball));
		fireCooldown = FIRE_COOLDOWN_TIME;
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

		bool isLeftSolid = tileManager->IsSolid(left, top);
		bool isRightSolid = tileManager->IsSolid(right, top);

		if (isLeftSolid || isRightSolid)
		{
			bool slided = false;
			// 角での滑り処理
			// 左の角に当たった
			if (isLeftSolid && !isRightSolid)
			{
				float overlap = (float)((left + 1) * TILE_SIZE) - pos.x;
				// 重なりが閾値以下なら、右に押し出す
				if (overlap > 0.0f && overlap < 4.0f)
				{
					pos.x += overlap;
					slided = true;
				}
			}
			// 右の角に当たった
			else if (!isLeftSolid && isRightSolid)
			{
				float overlap = (pos.x + size.w) - (float)(right * TILE_SIZE);
				// 重なりが閾値以下なら、左に押し出す
				if (overlap > 0.0f && overlap < 4.0f)
				{
					pos.x -= overlap;
					slided = true;
				}
			}

			// 滑らなかった場合、頭をぶつけた処理
			if (!slided)
			{
				// 衝突応答
				pos.y = static_cast<float>((top + 1) * TILE_SIZE);
				speed.y = 0.0f;
			}
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

	int color = GetColor(0, 255, 0);
	if (state == FIRE)
	{
		color = GetColor(255, 100, 100);
	}
	else if (state == SUPER)
	{
		color = GetColor(0, 150, 0);
	}

	DrawBox(drawX, drawY, drawX + size.w, drawY + size.h, color, true);

	DrawFormatString(0, 5, 0xFFFFFF, "Player pos:(%.2f %.2f)", pos.x, pos.y);

	DrawFormatString(0, 16, 0xFFFFFF, "isGrounded:%d", isGrounded);
	DrawFormatString(0, 32, 0xFFFFFF, "isCrouching:%d", isCrouching);
}

void Player::SetTileManager(TileManager* tm)
{
	tileManager = tm;
}

void Player::SetObjectManager(ObjectManager* om)
{
	objectManager = om;
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

void Player::GetFireFlower()
{
	switch (state)
	{
	case SMALL:
		state = SUPER;
		pos.y -= (SUPER_H - SMALL_H);
		break;
	case SUPER:
		state = FIRE;
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

	int top = py / TILE_SIZE;

	int bottom = (py + size.h - 1) / TILE_SIZE;

	//=====================================================
	// 右
	//=====================================================

	if (push > 0.0f)
	{
		int right = (px + size.w) / TILE_SIZE;

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

bool Player::CheckSquashEnemy(Enemy* enemy)
{

	if (enemy->canSquashed == false) return false;

	// マリオと敵の当たり判定
	bool isColliding = CheckBoxHit(pos, size, enemy->pos, enemy->size);

	if (!isColliding) return false;

	// 踏みつけ処理
	if (speed.y > 0.0f && (prevPos.y + size.h) <= enemy->pos.y)
	{
		pos.y = enemy->pos.y - size.h;

		speed.y = -4.5f;
		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			speed.y = -JUMP_POWER;
		}
		return true;
	}

	return false;

}

