#pragma once
#pragma once
#include "Scene.h"
#include "Title.h"
#include "Stage.h"
#include <memory>
#define SCREEN_W	768
#define SCREEN_H	720

	constexpr int TILE_SIZE = 16;
	constexpr int SCALE = 3;
	constexpr int DRAW_SIZE = TILE_SIZE * SCALE;
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

	void ChangeScene(int nextScene);
};
