#include "Gameover.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "SoundManager.h"
#include "ImageManager.h"
void Gameover::Init()
{
}
void Gameover::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_TITLE);
	}
}
void Gameover::Render()
{
	DrawString(100, 100, "Game Over", GetColor(255, 255, 255));
	DrawString(100, 150, "Press Enter Key", GetColor(255, 255, 255));
}
Gameover::~Gameover()
{
}
