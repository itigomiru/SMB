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

void Player::update()
{
	Input();
	Jump();
	ApplyGravity();
	CheckCollisionToTile();
	Move();
}

void Player::Input()
{
	if( CheckHitKey( KEY_INPUT_LEFT ) ){
		vel.x -= 0.05f;
	}
	else if( CheckHitKey( KEY_INPUT_RIGHT ) ){
		vel.x += 0.05f;
	}
	else{
		if (vel.x > 0.0f) {
			vel.x -= 0.05f;
		}
		else if(vel.x < 0.0f){
			vel.x += 0.05f;
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
	if(pos.y > 400.0f){
		pos.y = 400.0f;
		vel.y = 0.0f;
		isGrounded = true;
	}
	else {
		isGrounded = false;
	}
}

void Player::render()
{
	DrawBox( pos.x, pos.y, pos.x + size.w, pos.y + size.h, GetColor( 255, 0, 0 ), TRUE );
}