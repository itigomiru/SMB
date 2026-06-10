#include "Main.h"
#include "SceneManager.h"
#include "PreStage.h"
#include "Float2.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "PlayerData.h"

PreStage::PreStage(int stageNum)
{
	nextStage = stageNum;
}

void PreStage::Init()
{
	timer = 0;
}

void PreStage::Update()
{
	timer++;
	if (timer > DISPLAY_TIME)
	{
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_STAGE, nextStage);
	}
}

void PreStage::Render()
{
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), true);
	DrawGraph(88,  83, ImageManager::GetInstance().GetImage(IMAGE_UI_WORLD), true);
	DrawGraph(145, 83, ImageManager::GetInstance().GetImage(IMAGE_UI_LINE), true);

    DrawRectGraph(101, 104, 0, 0, 16, 16, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_SMALL), true);
	DrawGraph(126, 113, ImageManager::GetInstance().GetImage(IMAGE_X_SCENE), true);
	DrawRectGraph(143, 111, PlayerData::GetInstance().GetStock() * 8, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);

	int srcX = 1 * 8;
	DrawRectGraph(135, 83, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	if(nextStage == 0)srcX = 1 * 8;
	if (nextStage == 1)srcX = 4 * 8;
	DrawRectGraph(156, 83, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	


}

PreStage::~PreStage()
{
}