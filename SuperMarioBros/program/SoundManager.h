#pragma once

class SoundManager
{
public:
	static SoundManager& GetInstance();
	//--------------------------------------------------
	enum BGM_LIST {
		BGM_GROUND,
		BGM_UNDERGROUND,
		BGM_CASTLE,
		BGM_WORLD_CLEAR,
		BGM_STAGE_CLEAR,
		BGM_FLAGPOLE,
		BGM_GAME_OVER, 
		BGM_MARIODIE,
		BGM_STAR,
		BGM_WARNING,
		BGM_HR_GROUND,
		BGM_HR_UNDERGROUND,
		BGM_HR_CASTLE,
		BGM_HR_STAR,
		BGM_MAX,
	};
	//--------------------------------------------------
	enum SE_LIST {
		SE_1UP,
		SE_BOWSERFALLS,
		SE_BOWSERFIRE,
		SE_BREAKBLOCK,
		SE_BUMP,
		SE_COIN,
		SE_FIREBALL,
		SE_FIREWORKS,
		SE_JUMP_SMALL,
		SE_JUMP_SUPER,
		SE_KICK,
		SE_PIPE,
		SE_POWERUP,
		SE_POWERUP_APPEARS,
		SE_STOMP,
		SE_PAUSE,
		SE_MAX,

	};
	//--------------------------------------------------
	void StopAllBGM();
	void PlayBGM(int BGMnum);
	void PlayShotBGM(int BGMnum);
	void PlaySE(int SEnum);
	int GetBGMHandle(int BGMnum) const { return BGMs[BGMnum]; }
	int GetSEHandle(int SEnum) const { return SEs[SEnum]; }
private:
	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	int BGMs[BGM_MAX];	//	音声のハンドルを入れる配列

	int SEs[SE_MAX];	//	効果音のハンドルを入れる配列
};