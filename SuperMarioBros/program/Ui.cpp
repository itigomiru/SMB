#include "Main.h"
#include "SceneManager.h"
#include "Ui.h"
#include "Float2.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "PlayerData.h"


UI::UI()
{
}
void UI::SetTileManager(TileManager* tm)
{
	tileManager = tm;
}

void UI::Render()
{
	int srcX = 1 * 8;
	//マリオ
	DrawGraph(20, 10, ImageManager::GetInstance().GetImage(IMAGE_UI_MARIO), true);
	srcX = (PlayerData::GetInstance().GetScore() / 100000) * 8;
	DrawRectGraph(20, 18, 0, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = ((PlayerData::GetInstance().GetScore() / 10000) % 10) * 8;
	DrawRectGraph(28, 18, 0, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = ((PlayerData::GetInstance().GetScore() / 1000) % 10) * 8;
	DrawRectGraph(36, 18, 0, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = ((PlayerData::GetInstance().GetScore() / 100) % 10) * 8;
	DrawRectGraph(44, 18, 0, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = ((PlayerData::GetInstance().GetScore() / 10) % 10) * 8;
	DrawRectGraph(52, 18, 0, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = (PlayerData::GetInstance().GetScore() % 10) * 8;
	DrawRectGraph(60, 18, 0, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	//コイン
	DrawGraph(82, 18, ImageManager::GetInstance().GetImage(IMAGE_COIN_SCENE), true);
	DrawGraph(89, 20, ImageManager::GetInstance().GetImage(IMAGE_X_SCENE), true);
	srcX = (PlayerData::GetInstance().GetCoin() / 10) * 8;
	DrawRectGraph(96, 18, 0, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = (PlayerData::GetInstance().GetCoin() % 10) * 8;
	DrawRectGraph(104, 18, 0, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	//ワールド
	DrawGraph(135, 10, ImageManager::GetInstance().GetImage(IMAGE_UI_WORLD), true);
	DrawRectGraph(143, 18, 8, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	DrawGraph(151, 18, ImageManager::GetInstance().GetImage(IMAGE_UI_LINE), true);
	if (tileManager)
	{
		if (tileManager->GetCurrentStage() == 0)srcX = 1 * 8;
		if (tileManager->GetCurrentStage() == 1)srcX = 4 * 8;
		if (tileManager->GetCurrentStage() == 2)srcX = 1 * 8;
	}
	else(srcX = 1 * 8);
	DrawRectGraph(159, 18, 8, srcX, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	//タイム
	DrawGraph(190, 10, ImageManager::GetInstance().GetImage(IMAGE_UI_TIME), true);
	srcX = (PlayerData::GetInstance().GetTime() / 100) * 8;
	DrawRectGraph(197, 18, 24, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = ((PlayerData::GetInstance().GetTime() / 10) % 10) * 8;
	DrawRectGraph(205, 18, 0, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = (PlayerData::GetInstance().GetTime() % 10) * 8;
	DrawRectGraph(213, 18, 8, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);







}

UI::~UI()
{
}