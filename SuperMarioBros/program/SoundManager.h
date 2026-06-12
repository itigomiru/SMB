#pragma once

//--------------------------------------------------
enum BGM_LIST {
	BGM_GROUND,
	BGM_UNDERGROUND,
	BGM_CASTLE,
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
	SE_FLAGPOLE,
	SE_GAME_OVER,
	SE_JUMP_SMALL,
	SE_JUMP_SUPER,
	SE_KICK,
	SE_MARIODIE,
	SE_PIPE,
	SE_POWERUP,
	SE_POWERUP_APPEARS,
	SE_STAGE_CLEAR,
	SE_STOMP,
	SE_VINE,
	SE_WARNING,
	SE_WORLD_CLEAR,
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