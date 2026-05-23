#include "DxLib.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "ImageManager.h"
#include "Clear.h"

void Clear::Init()
{
}
void Clear::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_TITLE);
	}
}
void Clear::Render()
{
	DrawString(100, 100, "Clear", GetColor(255, 255, 255));
	DrawString(100, 150, "Press Enter Key", GetColor(255, 255, 255));
}
Clear::~Clear()
{
}