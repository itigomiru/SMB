#pragma once
enum IMAGE_LIST {
	IMAGE_PLAYER_SMALL,
	IMAGE_PLAYER_BIG,
	IMAGE_PLAYER_FIRE,
	IMAGE_BACK_GROUND,
	IMAGE_FIRE_BALL,
	IMAGE_FIRE_BALL_EFFECT,


	//里--------------
	IMAGE_PLAYER_SMALL_TO_BIG,
	IMAGE_PLAYER_BIG_TO_FIRE,
	IMAGE_BLOCK_BREAK,
	IMAGE_PLAYER_DEATH,
	IMAGE_SCORE,
	//----------------
	//丸山
	IMAGE_BLOCK,
	IMAGE_GROUND,
	IMAGE_STAIR_BLOCK,
	IMAGE_QUESTION_BLOCK,
	IMAGE_HITTED_BLOCK,
	IMAGE_PIPE_LEFT_TOP,
	IMAGE_PIPE_RIGHT_TOP,
	IMAGE_PIPE_LEFT_BOTTOM,
	IMAGE_PIPE_RIGHT_BOTTOM,
	IMAGE_UI_WORLD,
	IMAGE_UI_LINE,
	IMAGE_MARIO_SCENE,
	IMAGE_COIN_SCENE,
	IMAGE_X_SCENE,
	IMAGE_UI_NUMBER,

	//-----------------------------------------
	//川野
	IMAGE_ITEM_SUPERMASHROOM,
	IMAGE_ITEM_1UPMASHROOM,
	IMAGE_ITEM_FIREFLOWER,
	IMAGE_ITEM_STAR,
	IMAGE_COIN,
	IMAGE_ENEMY_GOOMBA,
	IMAGE_ENEMY_KOOPATROOPA,
	IMAGE_LIFT,


	IMAGE_MAX
};


class ImageManager
{
public:
	static ImageManager& GetInstance();
private:
	ImageManager();
	~ImageManager();
	ImageManager(const ImageManager&) = delete;
	ImageManager& operator=(const ImageManager&) = delete;

	int images[IMAGE_MAX];	//	画像のハンドルを入れる配列
public:
	int GetImage(int num) const { return images[num]; }
};