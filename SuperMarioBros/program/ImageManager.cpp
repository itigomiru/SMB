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
	//丸山
	images[IMAGE_BLOCK] = LoadGraph("data/image/image_block.png");
	images[IMAGE_GROUND] = LoadGraph("data/image/image_ground.png");
	images[IMAGE_STAIR_BLOCK] = LoadGraph("data/image/image_stair_block.png");
	images[IMAGE_QUESTION_BLOCK] = LoadGraph("data/image/image_question_block.png");
	images[IMAGE_HITTED_BLOCK] = LoadGraph("data/image/image_hitted_block.png");
	images[IMAGE_PIPE_LEFT_TOP] = LoadGraph("data/image/image_pipe_left_top.png");
	images[IMAGE_PIPE_RIGHT_TOP] = LoadGraph("data/image/image_pipe_right_top.png");
	images[IMAGE_PIPE_LEFT_BOTTOM] = LoadGraph("data/image/image_pipe_left_bottom.png");
	images[IMAGE_PIPE_RIGHT_BOTTOM] = LoadGraph("data/image/image_pipe_right_bottom.png");



	//--------------------------------------------------------------
}

ImageManager::~ImageManager()
{
	//	画像のハンドルを解放
	for (int i = 0; i < IMAGE_MAX; i++) {
		DeleteGraph(images[i]);
		images[i] = -1;
	}
}
