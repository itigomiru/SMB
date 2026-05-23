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
	images[IMAGE_PLAYER] = LoadGraph("image_player");
}

ImageManager::~ImageManager()
{
	//	画像のハンドルを解放
	for (int i = 0; i < IMAGE_MAX; i++) {
		DeleteGraph(images[i]);
		images[i] = -1;
	}
}
