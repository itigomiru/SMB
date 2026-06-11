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
	int off = 7;
	int srcX = 1 * 8;
	//マリオ
	DrawGraph(24, 10, ImageManager::GetInstance().GetImage(IMAGE_UI_MARIO), true);
	srcX = (PlayerData::GetInstance().GetScore() / 100000) * 8;
	DrawRectGraph(24, 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = ((PlayerData::GetInstance().GetScore() / 10000) % 10) * 8;
	DrawRectGraph(32, 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = ((PlayerData::GetInstance().GetScore() / 1000) % 10) * 8;
	DrawRectGraph(40 , 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = ((PlayerData::GetInstance().GetScore() / 100) % 10) * 8;
	DrawRectGraph(48 , 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = ((PlayerData::GetInstance().GetScore() / 10) % 10) * 8;
	DrawRectGraph(56 , 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = (PlayerData::GetInstance().GetScore() % 10) * 8;
	DrawRectGraph(64 , 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	//コイン
	DrawGraph(89 , 18, ImageManager::GetInstance().GetImage(IMAGE_COIN_SCENE), true);
	DrawGraph(96 , 20, ImageManager::GetInstance().GetImage(IMAGE_X_SCENE), true);
	srcX = (PlayerData::GetInstance().GetCoin() / 10) * 8;
	DrawRectGraph(103 , 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = (PlayerData::GetInstance().GetCoin() % 10) * 8;
	DrawRectGraph(111 , 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	//ワールド
	DrawGraph(142 , 10, ImageManager::GetInstance().GetImage(IMAGE_UI_WORLD), true);
	srcX = 1 * 8;
	DrawRectGraph(150 , 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	DrawGraph(158 , 18, ImageManager::GetInstance().GetImage(IMAGE_UI_LINE), true);

	if (tileManager)
	{
		if (tileManager->GetCurrentStage() == 0)
			srcX = 1 * 8;
		if (tileManager->GetCurrentStage() == 1)
			srcX = 4 * 8;
		if (tileManager->GetCurrentStage() == 2)
			srcX = 1 * 8;
	}
	else(srcX = 1 * 8);
	DrawRectGraph(166 , 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	//タイム
	DrawGraph(197 , 10, ImageManager::GetInstance().GetImage(IMAGE_UI_TIME), true);
	srcX = (PlayerData::GetInstance().GetTime() / 24 / 100) * 8;
	DrawRectGraph(204 , 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = ((PlayerData::GetInstance().GetTime() / 24 / 10) % 10) * 8;
	DrawRectGraph(212 , 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = (PlayerData::GetInstance().GetTime() / 24 % 10) * 8;
	DrawRectGraph(220 , 18, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);







}

UI::~UI()
{
}