#pragma once
enum IMAGE_LIST {
	IMAGE_PLAYER_SMALL,
	IMAGE_PLAYER_BIG,
	IMAGE_PLAYER_FIRE,
	IMAGE_BACK_GROUND,
	IMAGE_FIRE_BALL,
	IMAGE_FIRE_BALL_EFFECT,
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

	//-----------------------------------------
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