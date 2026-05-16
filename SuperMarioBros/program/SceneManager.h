#pragma once

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
	int scene_num;		//	今どこのシーンにいるのかを見る用の変数
	int scene_next;
	SceneManager();
	~SceneManager();

	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

public:
	void Init();	//	初期化処理
	void Update();	//	更新処理
	void Render();	//	描画処理
};





