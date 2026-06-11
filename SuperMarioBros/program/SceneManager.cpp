#include "Main.h"
#include "SceneManager.h"

#include "Title.h"	
#include "PreStage.h"	
#include "Stage.h"	
#include "Clear.h"	
#include "Ending.h"	
#include "Gameover.h"
#include "ImageManager.h"
#include"Ui.h"





//---------------------------------------------------------------------------------
//	èâä˙âªèàóù
//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
//	çXêVèàóù
//---------------------------------------------------------------------------------
void SceneManager::Update()
{
	currentScene->Update();
	ChangeScene();
}

//---------------------------------------------------------------------------------
//	ï`âÊèàóù
//---------------------------------------------------------------------------------
void SceneManager::Render()
{
	currentScene->Render();
	UI::GetInstance().Render();
}
//---------------------------------------------------------------------------------
//	èIóπèàóù

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


void SceneManager::ChangeScene() {
	if (reserveScene == -1) return; 
	switch (reserveScene) {
	case SCENE_TITLE:
		currentScene = std::make_unique<Title>();
		break;
	case SCENE_PRESTAGE:
		currentScene = std::make_unique<PreStage>(reserveStage);
		break;
	case SCENE_STAGE:
		currentScene = std::make_unique<Stage>(reserveStage);
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
	reserveScene = -1;
	reserveStage = 0;
}