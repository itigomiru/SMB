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
void SceneManager::Init()
{
	//	最初はタイトルから開始
	scene_num = SCENE_TITLE;
	scene_next = SCENE_TITLE;



	//	タイトル画面の初期化
	TitleInit();
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void SceneManager::Update()
{
	//	今のシーン番号と次に行きたいシーン番号が違っていたらシーンが切り替わるタイミング
	if( scene_num != scene_next ){
		//	今のシーン番号を新しく設定しなおして
		scene_num = scene_next;
		//	シーン番号に合わせた初期化処理を呼ぶ
		switch( scene_num ){
		case SCENE_TITLE:
			TitleInit();
			break;

		case SCENE_STAGE:
			StageInit();
			break;

		case SCENE_CLEAR:
			ClearInit();
			break;
		case SCENE_ENDING:
			EndingInit();
			break;
		case SCENE_GAMEOVER:
			GameoverInit();
			break;
			
		}
	}

	//	今のシーン番号に合わせた更新処理を呼ぶ
	switch( scene_num ){
	case SCENE_TITLE:
		TitleUpdate();
		break;

	case SCENE_STAGE:
		StageUpdate();
		break;

	case SCENE_CLEAR:
		ClearUpdate();
		break;
	case SCENE_ENDING:
		EndingUpdate();
		break;
	case SCENE_GAMEOVER:
		GameoverUpdate();
		break;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void SceneManager::Render()
{
	//	今のシーン番号に合わせた描画処理を呼ぶ
	switch( scene_num ){
	case SCENE_TITLE:
		TitleRender();
		break;

	case SCENE_STAGE:
		StageRender();
		break;

	case SCENE_CLEAR:
		ClearRender();
		break;
	case SCENE_ENDING:
		EndingRender();
		break;
	case SCENE_GAMEOVER:
		GameoverRender();
		break;
	}
	DrawRotaGraph(SCREEN_W * 0.8, SCREEN_H * 0.99 - 2, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_CREDIT), true);
	DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.99 - 2, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_LEVEL), true);
	
}
//---------------------------------------------------------------------------------
//	終了処理

SceneManager::SceneManager()
{
	// constructor
}

SceneManager::~SceneManager()
{
	TitleExit();
	StageExit();
	ClearExit();
}
