#include "Player.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Main.h"
Player::Player()
{
	pos = { 100.0f, 100.0f };
	vel = { 0.0f, 0.0f };
	size = { WIDTH, CHIBI_H };
	isDead = false;
}

void Player::Update()
{
	Input();
	Jump();
	ApplyGravity();
	Move();
	CheckCollisionToTile();
}

void Player::Input()
{
	if( CheckHitKey( KEY_INPUT_A ) ){
		vel.x -= 0.1f;
	}
	else if( CheckHitKey( KEY_INPUT_D ) ){
		vel.x += 0.1f;
	}
	else{
		if (vel.x > 0.0f) {
			vel.x -= 0.1f;
		}
		else if(vel.x < 0.0f){
			vel.x += 0.1f;
		}
		if(vel.x > -VEL_MIN && vel.x < VEL_MIN){
			vel.x = 0.0f;
		}
	}
}

void Player::Move()
{
	if( vel.x > VEL_MAX.x ){
		vel.x = VEL_MAX.x;
	}
	else if( vel.x < -VEL_MAX.x ){
		vel.x = -VEL_MAX.x;
	}
	if( vel.y > VEL_MAX.y ){
		vel.y = VEL_MAX.y;
	}
	else if( vel.y < -VEL_MAX.y ){
		vel.y = -VEL_MAX.y;
	}
	prevPos = pos;
	pos.x += vel.x;
	pos.y += vel.y;
}

void Player::Jump()
{
	if( PushHitKey( KEY_INPUT_SPACE ) && isGrounded){
		vel.y = -10.0f;
	}
}

void Player::ApplyGravity()
{
	vel.y += SceneManager::GetInstance().GRAVITY;
}

void Player::CheckCollisionToTile()
{
	float nextY = pos.y + vel.y;

	int tileX = pos.x / 16;

	int tileY =
		(nextY + size.h) / 16;

	if (tileManager->IsSolid(tileX, tileY))
	{
		pos.y =
			tileY * 16 - size.h;

		vel.y = 0;

		isGrounded = true;
	}
	else
	{
		isGrounded = false;
	}
}

void Player::Render(float cameraX)
{
	int drawX =
		(pos.x - cameraX) * 3;

	int drawY =
		pos.y * 3;

	DrawBox(
		drawX,
		drawY,
		drawX + 48,
		drawY + 48,
		GetColor(0, 255, 0),
		true);
}

 void Player::SetTileManager(TileManager* tm)
{
	tileManager = tm;
}

