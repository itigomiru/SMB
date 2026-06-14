#include "Player.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Enemy.h"
#include "Main.h"
#include "Fireball.h"
#include "ObjectManager.h"
#include "ImageManager.h"
#include "PlayerData.h"
#include "Stage.h"
#include "ScoreEffect.h"
#include "EffectManager.h"
#include "Hit.h"
#include "LiftController.h"

bool IsPress(int key, int padButton) {
	if (CheckKey(key)) return true;

	int padState = GetJoypadInputState(DX_INPUT_PAD1);
	if (padState & padButton) return true;

	return false;
}

bool IsPush(int key, int padButton) {
	if (PushHitKey(key)) return true;

	return false;
}

Player::Player(Float2 position)
{
	objectType = OT_PLAYER;
	renderLayer = RL_PLAYER;
	Init(position);
}


void Player::Init(Float2 position)
{
	isFacingRight = true;
	isDead = false;
	isGround = false;
	isCrouching = false;
	speed = { 0.0f, 0.0f };
	pos = position;
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
	isTryingToStand = false;
	standPushDir = 0.0f;
	starTimer = 0;
	fireballCount = 0;
	fireCooldown = 0;
	firePoseTimer = 0;
	isFallenDeath = false;
	deathSpeedY = 0.0f;
	firePoseTimer = 0;
	isOnLift = false;
	isGoal = false;
	goalPhase = GP_DOWN;
	comboCount = 0;
}


void Player::Update(float cameraX)
{
	if (tileManager->bridgeState == TileManager::BS_COLLAPSING || tileManager->bridgeState == TileManager::BS_COLLAPSED)return;
	prevPos = pos;
	if (pos.x - cameraX < 0)pos.x = cameraX;

	if (isEnteringPipe) {
		int currentStage = tileManager->GetCurrentStage();
		pipeAnimationTimer--;

		if (currentStage == 0) {
			pos.y += 0.8f;
		}
		else if (currentStage == 2) {
			pos.x += 0.8f;
		}

		if (pipeAnimationTimer <= 0) {
			isEnteringPipe = false;

			if (currentStage == 0) {
				tileManager->ChangeStage(2);
				if (starTimer == 0) SoundManager::GetInstance().PlayBGM(SoundManager::BGM_UNDERGROUND);
				pos.x = 2 * TILE_SIZE;
				pos.y = 2 * TILE_SIZE;
				renderLayer = RL_PLAYER;
				stage->cameraX = 0;
			}
			else if (currentStage == 2) {
				tileManager->ChangeStage(0);
				if (starTimer == 0) SoundManager::GetInstance().PlayBGM(SoundManager::BGM_GROUND);
				stage->cameraX = 160 * TILE_SIZE;
				pos.x = 163 * TILE_SIZE + (TILE_SIZE / 2);
				pos.y = 9 * TILE_SIZE;
				renderLayer = RL_PLAYER;
			}
		}

		return;
	}

	if (freezeTimer > 0)
	{
		PowerUpUpdate();
		return;
	}
	if (starTimer > 0)
	{
		starTimer--;
		if (starTimer == 1)
		{
			int handle;
			if (tileManager->GetCurrentStage() == 0)handle = SoundManager::BGM_GROUND;
			else if (tileManager->GetCurrentStage() == 1)handle = SoundManager::BGM_CASTLE;
			else handle = SoundManager::BGM_UNDERGROUND;
			SoundManager::GetInstance().PlayBGM(handle);
		}
	}

	isGround = CheckGround();
	if (CheckLift())
	{
		isGround = true;
		isJumping = false;
		isAnimJamping = false;
	}
	if (isGround)
	{
		isAnimJamping = false;
		comboCount = 0;
	}

#if 1
	// デバッグ用キー
	if (PushHitKey(KEY_INPUT_0)) { GetSuperMashroom(); }
	if (PushHitKey(KEY_INPUT_9)) { GetFireFlower(); }
	if (PushHitKey(KEY_INPUT_8)) { GetStar(); }
	if (PushHitKey(KEY_INPUT_7)) { Get1UpMushroom(); }
#endif
	if (fireCooldown > 0)fireCooldown--;
	if (firePoseTimer > 0)firePoseTimer--;

	if (tileManager->bridgeState == TileManager::BS_CLEAR)
	{
		speed.x = 1.0f;
		isFacingRight = true;
		if (pos.x > 2416)
		{
			speed.x = 0.0f;
			if (!CheckSoundMem(SoundManager::GetInstance().GetBGMHandle(SoundManager::BGM_WORLD_CLEAR)) && PushHitKey(KEY_INPUT_LSHIFT))SceneManager::GetInstance().ReserveScene(SceneManager::SCENE_TITLE);
		}
		UpdatePlayerSize();
		ApplyGravity();
		MoveX();
		MoveY();
		CheckCollisionY();
		return;
	}

	if (isGoal)
	{
		GoalUpdate();
		UpdatePlayerSize();
		ApplyGravity();
		MoveX();
		MoveY();
		CheckCollisionY();
		return;
	}

	PlayerData::GetInstance().AddTime(-1);
	if (PlayerData::GetInstance().GetTime() == 100 * 24)
	{
		SoundManager::GetInstance().PlayShotBGM(SoundManager::BGM_WARNING);
	}
	if (PlayerData::GetInstance().GetTime() < 100 * 24)
	{
		if (!CheckSoundMem(SoundManager::GetInstance().GetBGMHandle(SoundManager::BGM_WARNING)) && !isDead)
		{
			int handle;
			if (tileManager->GetCurrentStage() == 0)handle = SoundManager::BGM_HR_GROUND;
			else if (tileManager->GetCurrentStage() == 1)handle = SoundManager::BGM_HR_CASTLE;
			else if (tileManager->GetCurrentStage() == 2)handle = SoundManager::BGM_HR_UNDERGROUND;
			if (starTimer > 0)handle = SoundManager::BGM_HR_STAR;


			if (!CheckSoundMem(SoundManager::GetInstance().GetBGMHandle(handle)))SoundManager::GetInstance().PlayBGM(handle);
		}
	}


	PipeCheck();
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
	if ((CheckKey(KEY_INPUT_S) || CheckKey(KEY_INPUT_DOWN)) && state != SMALL)
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
	if ((CheckKey(KEY_INPUT_A) || CheckKey(KEY_INPUT_LEFT)) && !isCrouching)
	{
		speed.x -= MOVE_ACCEL;
		if (speed.x > 0.05)speed.x -= MOVE_ACCEL;
		if (isGround)isFacingRight = false;
	}
	else if
		((CheckKey(KEY_INPUT_D) || CheckKey(KEY_INPUT_RIGHT)) && !isCrouching)
	{
		speed.x += MOVE_ACCEL;
		if (speed.x < 0.05)speed.x += MOVE_ACCEL * 2;
		if (isGround)isFacingRight = true;
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
	if (PushHitKey(KEY_INPUT_LSHIFT) && state == FIRE && fireCooldown == 0 && fireballCount < FIREBALL_MAX && !isCrouching)
	{
		Float2 fireballPos = pos;
		fireballPos.x += isFacingRight ? size.w : 0;
		fireballPos.y += size.h / 4;
		auto fireball = std::make_unique<Fireball>(fireballPos, isFacingRight, tileManager, objectManager);
		objectManager->AddObject(std::move(fireball));

		fireCooldown = FIRE_COOLDOWN_TIME;
		firePoseTimer = FIRE_POSE_TIME;
	}

	//=========================================================
	// 最大速度制限
	//=========================================================
	if (CheckKey(KEY_INPUT_LSHIFT))
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
		if (state == SMALL)SoundManager::GetInstance().PlaySE(SoundManager::SE_JUMP_SMALL);
		else SoundManager::GetInstance().PlaySE(SoundManager::SE_JUMP_SUPER);

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

		if (CheckKey(KEY_INPUT_SPACE) && speed.y < 0.0f && isJumping)
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
		isFallenDeath = true;
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

		// リフトの当たり判定
		for (const auto& obj : objectManager->GetObjects())
		{
			if (obj->objectType != Object::OT_LIFT) continue;
			if (obj->isDead) continue;

			Lift* lift = static_cast<Lift*>(obj.get());

			float playerLeft = pos.x;
			float playerRight = pos.x + size.w;
			float playerTop = pos.y;
			float prevPlayerTop = prevPos.y;

			float liftLeft = lift->pos.x;
			float liftRight = lift->pos.x + lift->size.w;
			float liftBottom = lift->pos.y + lift->size.h;

			bool hitX =
				playerRight > liftLeft &&
				playerLeft < liftRight;

			bool hitHead =
				prevPlayerTop >= liftBottom &&
				playerTop <= liftBottom;

			if (hitX && hitHead)
			{
				pos.y = liftBottom;
				speed.y = 0.0f;
				isJumping = false;
				break;
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

void Player::SetState(int newState)
{
	state = newState;
	UpdatePlayerSize();
	if (state != SMALL)
	{
		pos.y -= (SUPER_H - SMALL_H);
	}
}

void Player::GetSuperMashroom()
{
	SoundManager::GetInstance().PlaySE(SoundManager::SE_POWERUP);
	if (state == SMALL)
	{
		oldState = SMALL;
		newState = SUPER;
		isChangingState = true;
		freezeTimer = POWER_UP_TIME;

		pos.y -= (SUPER_H - SMALL_H);
	}
	EffectManager::GetInstance().AddEffect(std::make_unique<ScoreEffect>(pos, ScoreEffect::SCORE_1000));
}

void Player::Get1UpMushroom()
{
	PlayerData::GetInstance().AddStock(1);
	EffectManager::GetInstance().AddEffect(std::make_unique<ScoreEffect>(pos, ScoreEffect::SCORE_1UP));
}

void Player::GetFireFlower()
{
	SoundManager::GetInstance().PlaySE(SoundManager::SE_POWERUP);
	if (state == SMALL)
	{
		oldState = SMALL;
		newState = SUPER;
		isChangingState = true;
		freezeTimer = POWER_UP_TIME;

		pos.y -= (SUPER_H - SMALL_H);
	}
	else if (state == SUPER)
	{
		oldState = SUPER;
		newState = FIRE;
		isChangingState = true;
		freezeTimer = POWER_UP_TIME;
		SoundManager::GetInstance().PlaySE(SoundManager::SE_POWERUP);
	}
	EffectManager::GetInstance().AddEffect(std::make_unique<ScoreEffect>(pos, ScoreEffect::SCORE_1000));
}
void Player::GetStar()
{
	starTimer = STAR_TIME;
	SoundManager::GetInstance().PlaySE(SoundManager::SE_POWERUP);
	SoundManager::GetInstance().PlayBGM(SoundManager::BGM_STAR);
	EffectManager::GetInstance().AddEffect(std::make_unique<ScoreEffect>(pos, ScoreEffect::SCORE_1000));
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
		SoundManager::GetInstance().PlaySE(SoundManager::SE_STOMP);
		pos.y = enemy->pos.y - size.h;

		speed.y = -SQUASH_BOUNCE_POWER;
		EffectManager::GetInstance().AddEffect(std::make_unique<ScoreEffect>(enemy->pos, static_cast<ScoreEffect::SCORE>(comboCount)));
		if (comboCount == ScoreEffect::SCORE_1UP)
		{
			PlayerData::GetInstance().AddStock(1);
		}
		comboCount++;
		if (comboCount > ScoreEffect::SCORE_1UP) comboCount = ScoreEffect::SCORE_1UP;
		return true;
	}

	return false;

}

void Player::PowerUpUpdate()
{
	freezeTimer--;

	if (freezeTimer <= 0)
	{

		if (oldState != SMALL && newState == SMALL)
		{
			pos.y += (SUPER_H - SMALL_H);
		}

		state = newState;
		isChangingState = false;

		UpdatePlayerSize();
	}
}

void Player::Death()
{
	if (isDead) return;
	SoundManager::GetInstance().PlayShotBGM(SoundManager::BGM_MARIODIE);

	isDead = true;
	deathTimer = DEATH_TIME;

	if (!isFallenDeath)
	{
		deathSpeedY = 0.0f;
	}
	PlayerData::GetInstance().SetPlayerState(SMALL);
}

void Player::DeathUpdate()
{
	deathTimer--;

	if (isFallenDeath) return;

	if (deathTimer == DEATH_TIME - 20)
	{
		deathSpeedY = -DEATH_JUMP_POWER;
	}
	else if (deathTimer < DEATH_TIME - 20)
	{
		pos.y += deathSpeedY;
		deathSpeedY += SceneManager::GetInstance().GRAVITY;
	}
}

void Player::Damage()
{
	if (invincibleTimer > 0 || freezeTimer > 0) return;

	if (state == FIRE || state == SUPER)
	{
		SoundManager::GetInstance().PlaySE(SoundManager::SE_PIPE);
		oldState = state;
		newState = SMALL;
		isChangingState = true;
		freezeTimer = POWER_UP_TIME;

		// 無敵時間を付与
		invincibleTimer = INVINCIBLE_TIME;
	}
	else
	{
		isFallenDeath = false;
		Death();
	}
}

void Player::Render(float cameraX)
{
	int tileX = static_cast<int>(pos.x + size.w / 2) / TILE_SIZE;
	int tileY = static_cast<int>(pos.y + size.h + 1) / TILE_SIZE;
	if (isDead)
	{
		if (isFallenDeath) return;

		int drawX = static_cast<int>(pos.x) - static_cast<int>(cameraX);
		int drawY = static_cast<int>(pos.y);

		DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_DEATH), true);

		return;
	}
	// 被弾後の通常の点滅（変身アニメーション中でない場合のみ）
	if (!isChangingState && invincibleTimer > 0)
	{
		if ((invincibleTimer / 4) % 2 == 0)
		{
			return;
		}
	}

	if (isGround && std::abs(speed.x) > 0.05f && freezeTimer == 0) {
		animeCount += std::abs(speed.x);
	}
	else if (freezeTimer == 0) {
		animeCount = 0.0f;
	}


	if (isChangingState)
	{
		int drawX = static_cast<int>(pos.x) - static_cast<int>(cameraX);
		int drawY = static_cast<int>(pos.y);
		int srcX = 0;
		int chipW = 16;
		int chipH = 32;

		if ((oldState == SMALL && newState == SUPER) || (oldState != SMALL && newState == SMALL))
		{
			if (freezeTimer <= 12)
			{
				if (newState == SUPER) {
					srcX = 32;
				}
				else {
					srcX = 0;
				}
			}
			else
			{
				int framePattern;
				if (oldState == SMALL && newState == SUPER)framePattern = ((POWER_UP_TIME - freezeTimer) / 4) % 3;
				else  framePattern = (freezeTimer / 4) % 3;

				srcX = framePattern * chipW;
			}

			if (((oldState != SMALL && newState == SMALL)) && freezeTimer / 4 % 2)return;
			// 画像を描画
			int handle = ImageManager::GetInstance().GetImage(IMAGE_PLAYER_SMALL_TO_BIG);
			if (isFacingRight) {
				DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, handle, true);
			}
			else {
				DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, handle, true, true);
			}
		}
		else
		{
			if (freezeTimer <= 12)
			{
				RenderFire(cameraX);
			}
			else
			{
				int framePattern;
				framePattern = ((POWER_UP_TIME - freezeTimer) / 4) % 4;

				srcX = framePattern * chipW;
				// 画像を描画
				int handle = ImageManager::GetInstance().GetImage(IMAGE_PLAYER_BIG_TO_FIRE);

				if (isFacingRight) {
					DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, handle, true);
				}
				else {
					DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, handle, true, true);
				}
			}
		}
	}
	else
	{
		if (starTimer / 4 % 2 == 1)SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);
		// 通常時の描画
		switch (state)
		{
		case SMALL: RenderSmall(cameraX); break;
		case SUPER: RenderBig(cameraX);   break;
		case FIRE:  RenderFire(cameraX);  break;
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	if (pos.x > 2416 && tileManager->bridgeState == TileManager::BS_CLEAR && !CheckSoundMem(SoundManager::GetInstance().GetBGMHandle(SoundManager::BGM_WORLD_CLEAR)))DrawGraph(17, 65, ImageManager::GetInstance().GetImage(IMAGE_CLEAR_MESSAGE), true);
}
void Player::RenderSmall(float cameraX)
{
	int chipW = 16;
	int chipH = 16;
	int srcX = 0;

	bool isBraking = false;

	// 逆キーが押されている場合はブレーキアニメーション
	if (speed.x > 0.1f && (CheckKey(KEY_INPUT_A) || CheckKey(KEY_INPUT_LEFT)) && !isGoal) {
		isBraking = true;
	}
	else if (speed.x < -0.1f && (CheckKey(KEY_INPUT_D) || CheckKey(KEY_INPUT_RIGHT)) && !isGoal) {
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
		DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_SMALL), true, true);
	}
}
void Player::RenderBig(float cameraX)
{
	int chipW = 16;
	int chipH = 32;
	int srcX = 0;

	bool isBraking = false;

	// 逆キーが押されている場合はブレーキアニメーション
	if (speed.x > 0.1f && (CheckKey(KEY_INPUT_A) || CheckKey(KEY_INPUT_LEFT)) && !isGoal) {
		isBraking = true;
	}
	else if (speed.x < -0.1f && (CheckKey(KEY_INPUT_D) || CheckKey(KEY_INPUT_RIGHT)) && !isGoal) {
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

	if (isCrouching) {
		drawY -= 16;
		srcX = chipW * 6; // しゃがみポーズ
	}

	if (isFacingRight) {
		DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_BIG), true);
	}
	else {
		DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_BIG), true, true);
	}
}

void Player::RenderFire(float cameraX)
{
	int chipW = 16;
	int chipH = 32;
	int srcX = 0;

	bool isBraking = false;

	// 逆キーが押されている場合はブレーキアニメーション
	if (speed.x > 0.1f && (CheckKey(KEY_INPUT_A) || CheckKey(KEY_INPUT_LEFT)) && !isGoal) {
		isBraking = true;
	}
	else if (speed.x < -0.1f && (CheckKey(KEY_INPUT_D) || CheckKey(KEY_INPUT_RIGHT)) && !isGoal) {
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
		drawY -= 16;
		srcX = chipW * 6; // しゃがみポーズ
	}
	if (firePoseTimer > 0)
	{
		srcX = chipW * 7;
	}


	if (isFacingRight) {
		DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_FIRE), true);
	}
	else
	{
		DrawRectGraph(drawX, drawY, srcX, 0, chipW, chipH, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_FIRE), true, true);
	}
}



void Player::RenderStar(float cameraX)
{
	int chipW = 16;

}

void Player::PipeCheck() {
	// すでに土管アニメーション中なら、ここのキー判定はスキップ
	if (isEnteringPipe) return;

	int currentStage = tileManager->GetCurrentStage();
	int tileX = static_cast<int>(pos.x + size.w / 2) / TILE_SIZE;
	int tileY = static_cast<int>(pos.y + size.h + 1) / TILE_SIZE;

	if (currentStage == 0) {
		if (pos.x > 916 && pos.x < 926 && tileY == 9 && isGround) {
			if ((CheckKey(KEY_INPUT_S) || CheckKey(KEY_INPUT_DOWN))) {
				// アニメーション開始の合図
				isEnteringPipe = true;
				pipeAnimationTimer = PIPE_ANIMATION_TIME;
				speed.x = 0;
				speed.y = 0;
				renderLayer = Object::RL_UNDER_TILE;
				SoundManager::GetInstance().PlaySE(SoundManager::SE_PIPE);
			}
		}
	}
	else if (currentStage == 2) {
		if (pos.x > 191 && tileY >= 12 && (CheckKey(KEY_INPUT_D) || CheckKey(KEY_INPUT_RIGHT)) && isGround) {
			isEnteringPipe = true;
			renderLayer = Object::RL_UNDER_TILE;
			pipeAnimationTimer = PIPE_ANIMATION_TIME;
			speed.x = 0;
			speed.y = 0;
			SoundManager::GetInstance().PlaySE(SoundManager::SE_PIPE);
		}
	}
}

void Player::SetStage(Stage* st)
{
	stage = st;
}

void Player::LandingOnGround()
{
	speed.y = 0.0f;
	isGround = true;
	isJumping = false;
	isAnimJamping = false;
}

bool Player::CheckLift()
{
	if (speed.y < 0.0f) return false;

	for (const auto& obj : objectManager->GetObjects())
	{
		if (obj->objectType != Object::OT_LIFT) continue;
		if (obj->isDead) continue;

		Lift* lift = static_cast<Lift*>(obj.get());

		bool hitX =
			pos.x + size.w > lift->pos.x &&
			pos.x < lift->pos.x + lift->size.w;

		bool onTop =
			pos.y + size.h >= lift->pos.y - 2.0f &&
			pos.y + size.h <= lift->pos.y + 6.0f;

		if (hitX && onTop)
		{
			pos.y = lift->pos.y - size.h;
			speed.y = 0.0f;

			pos.x += lift->GetMoveX();

			return true;
		}
	}

	return false;
}
void Player::OnGoal(float poleCenterX)
{
	if (isGoal || isDead) return;
	SoundManager::GetInstance().PlayShotBGM(SoundManager::BGM_FLAGPOLE);
	isGoal = true;
	goalPhase = GP_DOWN;

	pos.x = poleCenterX - size.w;

	speed.x = 0.0f;
	speed.y = 0.0f;
	isFacingRight = true;


	isCrouching = false;
	isJumping = false;
	isAnimJamping = false;


}
void Player::GoalUpdate()
{
	if (tileManager->GetCurrentStage() == 0)
	{

		switch (goalPhase)
		{
		case GP_DOWN: // ポールをスライドして降りる
			speed.x = 0.0f;
			speed.y = 1.0f; // 一定速度で下へ

			// 地面に着地したら次のフェーズへ
			if (isGround && CheckSoundMem(SoundManager::GetInstance().GetBGMHandle(SoundManager::BGM_FLAGPOLE)) == 0)
			{
				pos.x += size.w;
				goalPhase = 1;
				speed.y = 0.0f;
				isFacingRight = true; // 右を向く
				SoundManager::GetInstance().PlayShotBGM(SoundManager::BGM_STAGE_CLEAR);
			}
			break;

		case GP_WALK:
			speed.x = 1.0f;

			if (pos.x > 3270)
			{
				speed.x = 0.0f;
				if (CheckSoundMem(SoundManager::GetInstance().GetBGMHandle(SoundManager::BGM_STAGE_CLEAR)) == 0)
				{
					SceneManager::GetInstance().ReserveScene(SceneManager::SCENE_PRESTAGE, 1);
					PlayerData::GetInstance().SetPlayerState(state);
				}
			}
			break;
		}
	}
	if (tileManager->GetCurrentStage() == 1)
	{
		switch (goalPhase)
		{
		case GP_DOWN:
			if (isGround)
			{
				pos.x += size.w;
				goalPhase = GP_WALK;
				speed.y = 0.0f;
				isFacingRight = true; // 右を向く
			}
			break;
		case GP_WALK:
			//speed.x = 1.0f;
			//if (pos.x > 12 * TILE_SIZE)
			//{
			//	speed.x = 0.0f;
			//	SceneManager::GetInstance().ReserveScene(SceneManager::SCENE_PRESTAGE, 1);
			//	PlayerData::GetInstance().SetPlayerState(state);
			//}
			break;
		}
	}

	return;
}