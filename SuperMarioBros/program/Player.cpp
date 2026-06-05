#include "Player.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "Main.h"
#include "Fireball.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "PlayerData.h"
#include "Hit.h"

Player::Player()
{
	objectType = OT_PLAYER;
	renderLayer = RL_PLAYER;
	Init();
}

void Player::Init()
{
	isFacingRight = true;
	isDead = false;
	isGround = false;
	isCrouching = false;
	speed = { 0.0f, 0.0f };
	pos = { 20.0f, 150.0f };
	prevPos = pos;
	state = SMALL;
	size =
	{
		WIDTH,
		SMALL_H
	};
	isFacingRight = true;
	isDead = false;
	isGround = false;
	isCrouching = false;
	isJumping = false;
	isAnimJamping = false;
	isStar = false;
	isTryingToStand = false;
	standPushDir = 0.0f;
	starTimer = 0;
	fireballCount = 0;
	fireCooldown = 0;
}


void Player::Update(float cameraX)
{
	prevPos = pos;
	isGround = CheckGround();
	if (isGround)isAnimJamping = false;

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
	if (CheckHitKey(KEY_INPUT_S) &&state != SMALL)
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
		if(isGround)isFacingRight = false;
	}
	else if
		(CheckHitKey(KEY_INPUT_D) && !isCrouching)
	{
		speed.x += MOVE_ACCEL;
		if(isGround)isFacingRight = true;
	}
	else
	{
		if (isGround)
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
	if (CheckHitKey(KEY_INPUT_LSHIFT))
	{
		if (speed.x > DASH_SPEED_MAX)
		{
			speed.x = DASH_SPEED_MAX;
		}
		else if (speed.x < -DASH_SPEED_MAX)
		{
			speed.x = -DASH_SPEED_MAX;
		}
	}
	else {

		if (speed.x > SPEED_MAX.x)
		{
			speed.x = SPEED_MAX.x;
		}
		else if (speed.x < -SPEED_MAX.x)
		{
			speed.x = -SPEED_MAX.x;
		}
	}
}

void Player::Jump()
{
	if (PushHitKey(KEY_INPUT_SPACE) && isGround)
	{
		speed.y = -JUMP_POWER;

		if (speed.x > DASH_JUDGE_SPEED || speed.x < -DASH_JUDGE_SPEED)
		{
			speed.y *= DASH_JUNP_POWER_MULTIPLIER;
			// ダッシュジャンプの高さを上げる
		}

		isJumping = true;
		isAnimJamping = true;
		isGround = false;
	}
	if (speed.y > 0.0f)isJumping = false;
}


void Player::ApplyGravity()
{
	if (!isGround)
	{
		float gravity = SceneManager::GetInstance().GRAVITY;

		if (CheckHitKey(KEY_INPUT_SPACE) && speed.y < 0.0f && isJumping)
		{
			gravity *= 0.35f;
		}

		speed.y += gravity;


		if (speed.y > SPEED_MAX.y)
		{
			speed.y = SPEED_MAX.y;
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
	int px = static_cast<int>(pos.x);

	int py = static_cast<int>(pos.y);

	int top = py / TILE_SIZE;

	int bottom = (py + size.h - 1) / TILE_SIZE;

	int middle = (py + size.h / 2) / TILE_SIZE;
	//=========================================================
	// 右移動
	//=========================================================

	if (speed.x > 0.0f)
	{
		int right = (px + size.w) / TILE_SIZE;

		if (tileManager->IsSolid(right, top) || tileManager->IsSolid(right, bottom) || tileManager->IsSolid(right, middle))
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
		int left = px / TILE_SIZE;

		if (tileManager->IsSolid(left, top) || tileManager->IsSolid(left, bottom) || tileManager->IsSolid(left, middle))
		{
			pos.x = static_cast<float>((left + 1) * TILE_SIZE);

			speed.x = 0.0f;
		}
	}
}

void Player::CheckCollisionY()
{
	int px = static_cast<int>(pos.x);

	int py = static_cast<int>(pos.y);

	int left = px / TILE_SIZE;

	int right = (px + size.w - 1) / TILE_SIZE;

	//=========================================================
	// 下方向
	//=========================================================

	if (speed.y > 0.0f)
	{
		int bottom =
			(py + size.h - 1)
			/ TILE_SIZE;

		if (tileManager->IsSolid(left, bottom) || tileManager->IsSolid(right, bottom))
		{
			pos.y = static_cast<float>(bottom * TILE_SIZE - size.h);

			speed.y = 0.0f;

			isGround = true;
			isAnimJamping = false;
		}
	}
	if (py > SCREEN_H)
	{
		Death();
	}

	//=========================================================
	// 上方向
	//=========================================================

	else if (speed.y < 0.0f)
	{
		int top = py / TILE_SIZE;

		bool isLeftSolid = tileManager->IsSolid(left, top) || tileManager->IsHidden(left, top);
		bool isRightSolid = tileManager->IsSolid(right, top) || tileManager->IsHidden(right, top);

		if (isLeftSolid || isRightSolid)
		{
			bool slided = false;
			// 角での滑り処理
			// 左の角に当たった
			if (isLeftSolid && !isRightSolid)
			{
				float overlap = (float)((left + 1) * TILE_SIZE) - pos.x;
				// 重なりが閾値以下なら、右に押し出す
				if (overlap > 0.0f && overlap < OVERLAP_JUDGE)
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
				if (overlap > 0.0f && overlap < OVERLAP_JUDGE)
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

				int center;
				if (isLeftSolid && isRightSolid)
				{
					// プレイヤーの中心に近い方を叩く
					float playerCenterX = pos.x + size.w / 2.0f;
					float boundaryX = (float)(left + 1) * TILE_SIZE;
					if (playerCenterX < boundaryX)
					{
						center = left;
					}
					else
					{
						center = right;
					}
				}
				else if (isLeftSolid)
				{
					center = left;
				}
				else // isRightSolid
				{
					center = right;
				}

				if (state != SMALL)
				{
					tileManager->HitTile(center, top, false);
				}
				else
				{
					tileManager->HitTile(center, top, true);
				}
			}
		}
	}
}

bool Player::CheckGround()
{
	int px = static_cast<int>(pos.x);

	int py = static_cast<int>(pos.y);

	int left = px / TILE_SIZE;

	int right = (px + size.w - 1) / TILE_SIZE;

	int bottom = (py + size.h) / TILE_SIZE;

	return tileManager->IsSolid(left, bottom) || tileManager->IsSolid(right, bottom);
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

		pos.y -= (SUPER_H - SMALL_H);

		freezeTimer = POWER_UP_TIME;
		break;
	case SUPER:
		break;

	case FIRE:
		break;
	}
}

void Player::Get1UpMushroom()
{
	PlayerData::GetInstance().AddStock(1);
}

void Player::GetFireFlower()
{
	switch (state)
	{
	case SMALL:
		state = SUPER;
		pos.y -= (SUPER_H - SMALL_H);
		freezeTimer = POWER_UP_TIME;
		break;
	case SUPER:
		state = FIRE;
		freezeTimer = POWER_UP_TIME;
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

	// 踏みつけ処理
	if (speed.y > 0.0f && (prevPos.y + size.h) <= enemy->pos.y)
	{
		pos.y = enemy->pos.y - size.h;

		speed.y = -SQUASH_BOUNCE_POWER;
		return true;
	}

	return false;

}

void Player::PowerUpUpdate()
{
	freezeTimer--;
	if (state == SUPER)
	{
		//animation suru
	}
	else if (state == FIRE)
	{
		//animation suru
	}
}

void Player::Death()
{
	isDead = true;
	deathTimer = DEATH_TIME;
}

void Player::DeathUpdate()
{
	deathTimer--;
	// 死亡アニメーション
}

void Player::Damage()
{
	if (invincibleTimer > 0)
	{
		return;
	}
	if (state == FIRE)
	{
		state = SMALL;
		pos.y += (SUPER_H - SMALL_H);
		invincibleTimer = INVINCIBLE_TIME;

	}
	else if (state == SUPER)
	{
		state = SMALL;
		pos.y += (SUPER_H - SMALL_H);
		invincibleTimer = INVINCIBLE_TIME;
	}
	else
	{
		Death();
	}
}

void Player::Render(float cameraX)
{
	if (invincibleTimer > 0)
	{
		if ((invincibleTimer / 4) % 2 == 0)
		{
			return; // 点滅
		}
	}

	if (isGround && std::abs(speed.x) > 0.05f) {
		animeCount += std::abs(speed.x);
	}
	else {
		animeCount = 0.0f; // 停止時はリセット
	}

	switch (state)
	{
	case SMALL:
		RenderSmall(cameraX);
		break;
	case SUPER:
		RenderBig(cameraX);
		break;
	case FIRE:
		RenderFire(cameraX);
		break;
	}

	//DrawBox(drawX, drawY, drawX + size.w, drawY + size.h, color, true);

	DrawFormatString(0, 5, 0xFFFFFF, "Player pos:(%.2f %.2f)", pos.x, pos.y);

	DrawFormatString(0, 16, 0xFFFFFF, "isGrounded:%d", isGround);
	DrawFormatString(0, 32, 0xFFFFFF, "isCrouching:%d", isCrouching);
}
void Player::RenderSmall(float cameraX)
{
	int chipW = 16;
	int chipH = 16;
	int srcX = 0;

	bool isBraking = false;

	// 逆キーが押されている場合はブレーキアニメーション
	if (speed.x > 0.1f && CheckHitKey(KEY_INPUT_A)) {
		isBraking = true;
	}
	else if (speed.x < -0.1f && CheckHitKey(KEY_INPUT_D)) {
		isBraking = true;
	}

	if (isAnimJamping) {
		srcX = chipW * 5; // ジャンプポーズ
	}
	else if (isBraking) {
		srcX = chipW * 4; 
	}
	else if (std::abs(speed.x) > 0.05f) 
	{
		int frame = (animeCount / 6) % 3;
		srcX = chipW + (frame * chipW); // 走りアニメーション
	}
	else
	{
		srcX = 0; // 立ちポーズ
	}

	int drawX = static_cast<int>(pos.x - cameraX);
	int drawY = static_cast<int>(pos.y);

	if (isFacingRight) {
		DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_SMALL), true);
	}
	else 
	{
		DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_SMALL), true,true);
	}
}
void Player::RenderBig(float cameraX)
{
	int chipW = 16;
	int chipH = 32;
	int srcX = 0;

	bool isBraking = false;

	// 逆キーが押されている場合はブレーキアニメーション
	if (speed.x > 0.1f && CheckHitKey(KEY_INPUT_A)) {
		isBraking = true;
	}
	else if (speed.x < -0.1f && CheckHitKey(KEY_INPUT_D)) {
		isBraking = true;
	}

	if (isAnimJamping)
	{
		srcX = chipW * 5; // ジャンプポーズ
	}
	else if (isBraking) {
		srcX = chipW * 4;
	}
	else if (std::abs(speed.x) > 0.05f)
	{
		int frame = (animeCount / 6) % 3;
		srcX = chipW + (frame * chipW); // 走りアニメーション
	}
	else
	{
		srcX = 0; // 立ちポーズ
	}

	int drawX = static_cast<int>(pos.x - cameraX);
	int drawY = static_cast<int>(pos.y);

	// しゃがみ時の補正
	if (isCrouching) {
		drawY += 8;
	}

	if (isFacingRight) {
		DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_BIG), true);
	}
	else {
		DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_BIG), true,true);
	}
}

void Player::RenderFire(float cameraX)
{
	int chipW = 16;
	int chipH = 32;
	int srcX = 0;

	bool isBraking = false;

	// 逆キーが押されている場合はブレーキアニメーション
	if (speed.x > 0.1f && CheckHitKey(KEY_INPUT_A)) {
		isBraking = true;
	}
	else if (speed.x < -0.1f && CheckHitKey(KEY_INPUT_D)) {
		isBraking = true;
	}


	if (isAnimJamping) {
		srcX = chipW * 5; // ジャンプポーズ
	}
	else if (isBraking) {
		srcX = chipW * 4;
	}
	else if (std::abs(speed.x) > 0.05f)
	{
		int frame = (animeCount / 6) % 3;
		srcX = chipW + (frame * chipW); // 走りアニメーション
	}
	else
	{
		srcX = 0; // 立ちポーズ
	}

	int drawX = static_cast<int>(pos.x - cameraX);
	int drawY = static_cast<int>(pos.y);

	// しゃがみ時の補正
	if (isCrouching) {
		drawY += 8;
	}

	if (isFacingRight) {
		DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_FIRE), true);
	}
	else 
	{
		DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_FIRE), true,true);
	}
}