#include "ImageManager.h"
#include "DxLib.h"
ImageManager& ImageManager::GetInstance()
{
	static ImageManager instance;
	return instance;
}

ImageManager::ImageManager()
{
	//	画像のハンドルを入れる配列を初期化
	for (int i = 0; i < IMAGE_MAX; i++) {
		images[i] = -1;
	}
	//-------------------------------------------------------------------
	images[IMAGE_PLAYER_SMALL] = LoadGraph("data/image/image_player_small.png");
	images[IMAGE_PLAYER_BIG] = LoadGraph("data/image/image_player_big.png");
	images[IMAGE_PLAYER_FIRE] = LoadGraph("data/image/image_player_fire.png");
	images[IMAGE_BACK_GROUND] = LoadGraph("data/image/image_back_ground.png");
	images[IMAGE_FIRE_BALL] = LoadGraph("data/image/image_fire_ball.png");
	images[IMAGE_FIRE_BALL_EFFECT] = LoadGraph("data/image/image_fire_ball_effect.png");

	//里----------------
	images[IMAGE_PLAYER_SMALL_TO_BIG] = LoadGraph("data/image/image_player_small_to_big.png");
	images[IMAGE_PLAYER_BIG_TO_FIRE] = LoadGraph("data/image/image_player_big_to_fire.png");
	
	//------------------
}

ImageManager::~ImageManager()
{
	//	画像のハンドルを解放
	for (int i = 0; i < IMAGE_MAX; i++) {
		DeleteGraph(images[i]);
		images[i] = -1;
	}
}
