#include "Main.h"
#include "SceneManager.h"
#include "Title.h"
#include "Float2.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "PlayerData.h"

void Title::Init()
{
	PlayerData::GetInstance().Reset();

}
  
int debug = 0;
void Title::Update()
{
    if (CheckHitKey(KEY_INPUT_RETURN)) {
        SceneManager::GetInstance().ReserveScene(SceneManager::SCENE_PRESTAGE,0);
    }
	if (CheckHitKey(KEY_INPUT_M))
	{
        SceneManager::GetInstance().ReserveScene(SceneManager::SCENE_PRESTAGE,1);
	}
}

void Title::Render()
{
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(132, 134, 225), true);
	DrawGraph(0, TILE_SIZE * 2, ImageManager::GetInstance().GetImage(IMAGE_BACK_GROUND), true);


	DrawGraph(40, 26, ImageManager::GetInstance().GetImage(IMAGE_TITLE), true);
	DrawGraph(89, 160, ImageManager::GetInstance().GetImage(IMAGE_TITLE_PLAY), true);
	for (int i = 0; i < 16; i++)
	{
		DrawGraph(i * TILE_SIZE, 208, ImageManager::GetInstance().GetImage(IMAGE_GROUND), true);
	}
	for (int i = 0; i < 16; i++)
	{
		DrawGraph(i * TILE_SIZE, 224, ImageManager::GetInstance().GetImage(IMAGE_GROUND), true);
	}
	DrawRectGraph(40, 192, 0, 0, 16, 16, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_SMALL), true);

}

Title::~Title()
{
}