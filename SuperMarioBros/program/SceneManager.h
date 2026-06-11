#pragma once
#pragma once
#include "Scene.h"
#include "Title.h"
#include "Stage.h"
#include <memory>
#define SCREEN_W	256
#define SCREEN_H	240

constexpr int TILE_SIZE = 16;
class SceneManager
{
public:
	static SceneManager& GetInstance();
	//	各シーンの番号
	enum {
		SCENE_TITLE,
		SCENE_PRESTAGE,
		SCENE_STAGE,	
		SCENE_CLEAR,	
		SCENE_ENDING,
		SCENE_GAMEOVER,
	};
private:
	std::unique_ptr<Scene> currentScene;
	SceneManager();
	~SceneManager();

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;
	int reserveScene = -1;
	int reserveStage = 0;
	void ChangeScene();
public:
	void Update();	//	更新処理
	void Render();	//	描画処理
	const float GRAVITY = 0.5f;

	void ReserveScene(int nextScene, int nextStage = 0) {
		reserveScene = nextScene;
		reserveStage = nextStage;
	}
};
