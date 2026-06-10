#include "Main.h"
#include "SceneManager.h"
#include "PreStage.h"
#include "Float2.h"
#include "ImageManager.h"
#include "SoundManager.h"

void PreStage::Init()
{

}

void PreStage::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_STAGE);
	}
}

void PreStage::Render()
{
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), true);

    DrawRectGraph(88, 104, 0, 0, 16, 16, ImageManager::GetInstance().GetImage(IMAGE_PLAYER_SMALL), true);
	DrawGraph(113, 113, ImageManager::GetInstance().GetImage(IMAGE_X_SCENE), true);
	DrawGraph(80, 83, ImageManager::GetInstance().GetImage(IMAGE_UI_WORLD), true);
	DrawGraph(137, 83, ImageManager::GetInstance().GetImage(IMAGE_UI_LINE), true);

	int srcX = 1 * 8;
	DrawRectGraph(127, 83, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	srcX = 2 * 8;
	DrawRectGraph(148, 83, srcX, 0, 8, 8, ImageManager::GetInstance().GetImage(IMAGE_UI_NUMBER), true);
	


}

PreStage::~PreStage()
{
}