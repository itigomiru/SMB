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
	images[IMAGE_BLOCK_BREAK] = LoadGraph("data/image/image_block_break.png");
	images[IMAGE_PLAYER_DEATH] = LoadGraph("data/image/image_player_death.png");
	images[IMAGE_UNDERGROUND] = LoadGraph("data/image/image_underground.png");
	images[IMAGE_UNDERGROUND_BLOCK] = LoadGraph("data/image/image_underground_block.png");
	images[IMAGE_UNDERGROUND_COIN] = LoadGraph("data/image/image_underground_coin.png");
	images[IMAGE_CASTLE_GROUND] = LoadGraph("data/image/image_castle_ground.png");
	images[IMAGE_CASTLE_BLOCK] = LoadGraph("data/image/image_castle_block.png");
	images[IMAGE_CASTLE_HITTED_BLOCK] = LoadGraph("data/image/image_castle_hitted_block.png");
	images[IMAGE_CASTLE_QUESTION_BLOCK] = LoadGraph("data/image/image_castle_question_block.png");
	images[IMAGE_PIPE_LEFT_TOP_UNDERGROUND] = LoadGraph("data/image/image_pipe_left_top_underground.png");
	images[IMAGE_PIPE_LEFT_BOTTOM_UNDERGROUND] = LoadGraph("data/image/image_pipe_left_bottom_underground.png");
	images[IMAGE_PIPE_RIGHT_TOP_UNDERGROUND] = LoadGraph("data/image/image_pipe_right_top_underground.png");
	images[IMAGE_PIPE_RIGHT_BOTTOM_UNDERGROUND] = LoadGraph("data/image/image_pipe_right_bottom_underground.png");
	images[IMAGE_PIPE_TOP_UNDERGROUND] = LoadGraph("data/image/image_pipe_top_underground.png");
	images[IMAGE_PIPE_BOTTOM_UNDERGROUND] = LoadGraph("data/image/image_pipe_bottom_underground.png");
	images[IMAGE_GOAL] = LoadGraph("data/image/image_goal.png");
	images[IMAGE_GOAL_CASTLE] = LoadGraph("data/image/image_goal_castle.png");
	images[IMAGE_GOAL_CASTLE_RIGHT] = LoadGraph("data/image/image_goal_castle_right.png");
	images[IMAGE_CASTLE_BRIDGE] = LoadGraph("data/image/image_castle_bridge.png");
	images[IMAGE_MAGMA_TOP] = LoadGraph("data/image/image_magma_top.png");
	images[IMAGE_MAGMA_BOTTOM] = LoadGraph("data/image/image_magma_bottom.png");
	images[IMAGE_AXE] = LoadGraph("data/image/image_axe.png");
	images[IMAGE_GOAL_FLAG] = LoadGraph("data/image/image_goal_flag.png");
	images[IMAGE_AXE_CHAIN] = LoadGraph("data/image/image_axe_chain.png");
	images[IMAGE_CLEAR_MESSAGE] = LoadGraph("data/image/image_clear_message.png");
	images[IMAGE_PRINCESS] = LoadGraph("data/image/image_princess.png");
	//------------------
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
	images[IMAGE_SCORE] = LoadGraph("data/image/image_score.png");
	images[IMAGE_UI_WORLD] = LoadGraph("data/image/image_ui_world.png");
	images[IMAGE_UI_LINE] = LoadGraph("data/image/image_ui_line.png");
	images[IMAGE_UI_NUMBER] = LoadGraph("data/image/image_ui_number.png");
	images[IMAGE_COIN_SCENE] = LoadGraph("data/image/image_coin_scene.png");
	images[IMAGE_X_SCENE] = LoadGraph("data/image/image_x_scene.png");
	images[IMAGE_UI_MARIO] = LoadGraph("data/image/image_ui_mario.png");
	images[IMAGE_UI_TIME] = LoadGraph("data/image/image_ui_time.png");
	images[IMAGE_TITLE] = LoadGraph("data/image/image_title.png");
	images[IMAGE_TITLE_PLAY] = LoadGraph("data/image/image_title_play.png");
	images[IMAGE_UI_GAMEOVER] = LoadGraph("data/image/image_ui_gameover.png");
	//------------------
	//川野
	images[IMAGE_ITEM_SUPERMASHROOM] = LoadGraph("data/image/image_supermashroom.png");
	images[IMAGE_ITEM_1UPMASHROOM] = LoadGraph("data/image/image_1upmashroom.png");
	images[IMAGE_ITEM_FIREFLOWER] = LoadGraph("data/image/image_fireflower.png");
	images[IMAGE_ITEM_STAR] = LoadGraph("data/image/image_star.png");
	images[IMAGE_COIN] = LoadGraph("data/image/image_coin.png");
	images[IMAGE_ENEMY_GOOMBA] = LoadGraph("data/image/image_goomba.png");
	images[IMAGE_ENEMY_KOOPATROOPA] = LoadGraph("data/image/image_koopatroopa.png");
	images[IMAGE_LIFT] = LoadGraph("data/image/image_lift.png");
	images[IMAGE_BULLET_BREATH] = LoadGraph("data/image/image_bullet_breath.png");
	images[IMAGE_ENEMY_BOWSER_WALK] = LoadGraph("data/image/image_bowser_walk.png");
	images[IMAGE_ENEMY_BOWSER_BREATH] = LoadGraph("data/image/image_bowser_breath.png");

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
