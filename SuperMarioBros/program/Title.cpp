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

void Title::Update()
{
    if (CheckHitKey(KEY_INPUT_RETURN)) {
        SceneManager::GetInstance().ReserveScene(SceneManager::SCENE_PRESTAGE,0);
    }
}

void Title::Render()
{
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(132, 134, 225), true);
	DrawGraph(0, TILE_SIZE * 2, ImageManager::GetInstance().GetImage(IMAGE_BACK_GROUND), true);

	DrawGraph(40, 26, ImageManager::GetInstance().GetImage(IMAGE_TITLE), true);
	DrawGraph(111, 160, ImageManager::GetInstance().GetImage(IMAGE_TITLE_PLAY), true);
	for (int i = 0; i < 16; i++)
	{
		DrawGraph(i * TILE_SIZE, 208, ImageManager::GetInstance().GetImage(IMAGE_GROUND), true);
	}
	for (int i = 0; i < 16; i++)
	{
		DrawGraph(i * TILE_SIZE, 224, ImageManager::GetInstance().GetImage(IMAGE_GROUND), true);
	}

}

Title::~Title()
{
}