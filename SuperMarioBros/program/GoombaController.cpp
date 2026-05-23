#include "GoombaController.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "Main.h"

Goomba::Goomba()
{
	pos = { 20.0f, 200.0f };
	objectType = OT_ENEMY;
	speed = { 0.0f, 0.0f };
	size = { WIDTH, HEIGHT };

	renderLayer = RL_ENEMY;

}
