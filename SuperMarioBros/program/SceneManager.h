#pragma once
#include "Scene.h"
#include <memory>
#define SCREEN_W	640
#define SCREEN_H	448
class SceneManager
{
public:
	static SceneManager& GetInstance();
	//	各シーンの番号
	enum {
		SCENE_TITLE,	//	０：タイトル
		SCENE_STAGE,	//	１：ステージ
		SCENE_CLEAR,	//	２：リザルト（結果表示画面）
		SCENE_ENDING,
		SCENE_GAMEOVER,
	};
private:
	std::unique_ptr<Scene> currentScene;
	SceneManager();
	~SceneManager();

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

public:
	void Update();	//	更新処理
	void Render();	//	描画処理
	const float GRAVITY = 0.5f;

	void ChangeScene(int nextScene) {
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
	}
};





