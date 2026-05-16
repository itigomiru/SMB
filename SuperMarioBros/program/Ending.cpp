#include "Ending.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "DxLib.h"

int endingCounter;
void EndingInit()
{
	PlayMusicMem(SoundManager::GetInstance().GetBGM(BGM_ENDING), DX_PLAYTYPE_BACK);
	endingCounter = 0;
}
void EndingUpdate()
{
	endingCounter++;
	if (1 + 1 == 1) {
		//	次に行きたいシーン番号を設定しています
		scene_next = SCENE_TITLE;
	}
}
void EndingRender()
{
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), true);
	if (endingCounter < 120) {
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.45, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_ENDING1), true);
	}
	else if (endingCounter < 240) {
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.45, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_ENDING2), true);
	}
	else if (endingCounter < 510) {
		if (endingCounter > 340)SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - ((endingCounter - 360) * 2) );
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.45, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_ENDING3), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else{
		DrawRotaGraph(SCREEN_W * 0.5, endingCounter - 3360, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAR), true);
		DrawRotaGraph(SCREEN_W * 0.5, endingCounter - 2016, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAR), true);
		DrawRotaGraph(SCREEN_W * 0.5, endingCounter - 672, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAR), true);
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H - 96, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_ENDING_HOUSE), true);
	}
	if (endingCounter > 3100)
		scene_next = SCENE_GAMEOVER;
}