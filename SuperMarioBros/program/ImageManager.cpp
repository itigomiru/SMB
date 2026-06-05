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
}

ImageManager::~ImageManager()
{
	//	画像のハンドルを解放
	for (int i = 0; i < IMAGE_MAX; i++) {
		DeleteGraph(images[i]);
		images[i] = -1;
	}
}
