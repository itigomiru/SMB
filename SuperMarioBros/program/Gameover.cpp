#include "Gameover.h"
#include "SceneManager.h"
#include "DxLib.h"
#include "SoundManager.h"
#include "ImageManager.h"
int gameoverCount;
void GameoverInit()
{
	gameoverCount = 0;
	PlayMusicMem(SoundManager::GetInstance().GetBGM(BGM_GAMEOVER), DX_PLAYTYPE_BACK);
}
void GameoverUpdate()
{
	gameoverCount++;
	if (gameoverCount > 360) {
		//	次に行きたいシーン番号を設定しています
		scene_next = SCENE_TITLE;
	}
}
void GameoverRender()
{
	DrawBox(0, 0, SCREEN_W, SCREEN_H, 0x000000, true);
	DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.45,2.0f,0 ,ImageManager::GetInstance().GetImage(IMAGE_GAMEOVER), true);
}
