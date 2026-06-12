#include "Gameover.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "SoundManager.h"
#include "ImageManager.h"
void Gameover::Init()
{
	timer = 0;
	SoundManager::GetInstance().PlayShotBGM(SoundManager::BGM_GAME_OVER);
}
void Gameover::Update()
{
	timer++;
	if (timer > GAMEOVER_DISPLAY_TIME)SceneManager::GetInstance().ReserveScene(SceneManager::SCENE_TITLE);
}
void Gameover::Render()
{
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), true);

	DrawGraph(90, SCREEN_H/2, ImageManager::GetInstance().GetImage(IMAGE_UI_GAMEOVER), true);
}
Gameover::~Gameover()
{

}
