#include "Ending.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "DxLib.h"
void Ending::Init()
{
}
void Ending::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_TITLE);
	}
}
void Ending::Render()
{
	DrawString(100, 100, "Ending", GetColor(255, 255, 255));
	DrawString(100, 150, "Press Enter Key", GetColor(255, 255, 255));
}
Ending::~Ending()
{
}