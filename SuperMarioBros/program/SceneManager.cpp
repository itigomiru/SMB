#include "Main.h"
#include "SceneManager.h"

#include "Title.h"	//	タイトル関係の関数を呼びたいので
#include "Stage.h"	//	ステージ関係の関数を呼びたいので
#include "Clear.h"	//	リザルト（結果表示画面）関係の関数を呼びたいので
#include "Ending.h"	//	エンディング関係の関数を呼びたいので
#include "Gameover.h"
#include "ImageManager.h"





//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void SceneManager::Update()
{
	currentScene->Update();
}

//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void SceneManager::Render()
{
	currentScene->Render();
}
//---------------------------------------------------------------------------------
//	終了処理

SceneManager::SceneManager()
{
	currentScene = std::make_unique<Title>();
}

SceneManager::~SceneManager()
{
}

SceneManager& SceneManager::GetInstance()
{
	static SceneManager instance;
	return instance;
}


void SceneManager::ChangeScene(int nextScene) {
	switch (nextScene) {
	case SCENE_TITLE:
		currentScene = std::make_unique<Title>();
		break;
	case SCENE_STAGE:
		currentScene = std::make_unique<Stage>();
		break;
	case SCENE_CLEAR:
		currentScene = std::make_unique<Clear>();
		break;
	case SCENE_ENDING:
		currentScene = std::make_unique<Ending>();
		break;
	case SCENE_GAMEOVER:
		currentScene = std::make_unique<Gameover>();
		break;
	default:
		break;
	}
	currentScene->Init();
}