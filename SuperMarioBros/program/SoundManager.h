#pragma once

//--------------------------------------------------
enum BGM_LIST {
	BGM_FAKE,
	BGM_MAX,
};
//--------------------------------------------------
enum SE_LIST {
	SE_FAKE,
	SE_MAX,
};
//--------------------------------------------------
class SoundManager
{
public:
	static SoundManager& GetInstance();
private:
	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
	
	int BGMs[BGM_MAX];	//	音声のハンドルを入れる配列

	int SEs[SE_MAX];	//	効果音のハンドルを入れる配列
public:
	int GetSE(int num) const { return SEs[num]; }
	int GetBGM(int num) const { return BGMs[num]; }
	void StopAllBGM() ;
};