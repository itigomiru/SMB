#include "Main.h"
#include "SceneManager.h"
#include "Title.h"
#include "Float2.h"
#include"ImageManager.h"
#include "SoundManager.h"

void Title::Init()
{
}

void Title::Update()
{
	if (CheckHitKey(KEY_INPUT_RETURN)) {
		SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_STAGE);
	}
}

void Title::Render()
{
	DrawString(100, 100, "Super Mario Bros", GetColor(255, 255, 255));
	DrawString(100, 150, "Press Enter Key", GetColor(255, 255, 255));
}
Title::~Title()
{
}