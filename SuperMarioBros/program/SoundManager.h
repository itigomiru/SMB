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
		SE_WORLD_CLEAR,
		SE_STAGE_CLEAR,
		SE_FLAGPOLE,
		SE_GAME_OVER, 
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
		SE_MARIODIE,
		SE_PIPE,
		SE_POWERUP,
		SE_POWERUP_APPEARS,
		SE_STOMP,
		SE_WARNING,
		SE_MAX,

	};
	//--------------------------------------------------
	void StopAllBGM();
	void PlayBGM(int BGMnum);
	void PlaySE(int SEnum);
private:
	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;

	int BGMs[BGM_MAX];	//	音声のハンドルを入れる配列

	int SEs[SE_MAX];	//	効果音のハンドルを入れる配列
};