#include "Main.h"
#include "SceneManager.h"
#include "Title.h"
#include "Float2.h"
#include"ImageManager.h"
#include "SoundManager.h"
//=================================================================================
//	タイトル画面の処理
//=================================================================================
int animFrame = 0;
const int ANIMINTERVAL = 10;
//---------------------------------------------------------------------------------
//	初期化
//---------------------------------------------------------------------------------
void TitleInit()
{
	animFrame = 0;
	PlayMusicMem(SoundManager::GetInstance().GetBGM(BGM_TITLE), DX_PLAYTYPE_BACK);
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void TitleUpdate()
{
	animFrame++;
	if (animFrame >= ANIMINTERVAL * 6)
	{
		animFrame = 0;
	}
	//	スペースキーを押したら
	if (PushHitKey(KEY_INPUT_SPACE)) {
		//	次に行きたいシーン番号を設定しています
		scene_next = SCENE_STAGE;
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void TitleRender()
{
	DrawString(100, 100, "This is Title.", GetColor(255, 255, 255));
	DrawExtendGraph(0, 0, SCREEN_W, SCREEN_H, ImageManager::GetInstance().GetImage(IMAGE_TITLE_BG), true);
	DrawRectRotaGraph(SCREEN_W * 0.2, SCREEN_H * 0.7, animFrame / ANIMINTERVAL * 48, 0, 48, 50, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_TITLE_BABBLEN), true);
	DrawRectRotaGraph(SCREEN_W * 0.8, SCREEN_H * 0.7 + 2, animFrame / ANIMINTERVAL * 48, 0, 48, 48, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_TITLE_BOBBLEN), true);
}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void TitleExit()
{
}
