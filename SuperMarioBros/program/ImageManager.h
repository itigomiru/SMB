#pragma once
enum IMAGE_LIST {
	IMAGE_FAKE,
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