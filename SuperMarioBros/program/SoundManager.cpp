#include "SoundManager.h"
#include "DxLib.h"



//========================================================
SoundManager& SoundManager::GetInstance()
{
	static SoundManager instance;
	return instance;
}

SoundManager::SoundManager()
{
	//	効果音のハンドルを入れる配列を初期化
	for (int i = 0; i < SE_MAX; i++) {
		SEs[i] = -1;
	}
	//---------------------------------------------------------
	SEs[SE_1UP] = LoadSoundMem("data/sound/se_1-up.wav");
	SEs[SE_BOWSERFALLS] = LoadSoundMem("data/sound/se_bowserfalls.wav");
	SEs[SE_BOWSERFIRE] = LoadSoundMem("data/sound/se_bowserfire.wav");
	SEs[SE_BREAKBLOCK] = LoadSoundMem("data/sound/se_breakblock.wav");
	SEs[SE_BUMP] = LoadSoundMem("data/sound/se_bump.wav");
	SEs[SE_COIN] = LoadSoundMem("data/sound/se_coin.wav");
	SEs[SE_FIREBALL] = LoadSoundMem("data/sound/se_fireball.wav");
	SEs[SE_FIREWORKS] = LoadSoundMem("data/sound/se_fireworks.wav");
	SEs[SE_FLAGPOLE] = LoadSoundMem("data/sound/se_flagpole.wav");
	SEs[SE_GAME_OVER] = LoadSoundMem("data/sound/se_gameover.wav");
	SEs[SE_JUMP_SMALL] = LoadSoundMem("data/sound/se_jump-small.wav");
	SEs[SE_JUMP_SUPER] = LoadSoundMem("data/sound/se_jump-super.wav");
	SEs[SE_KICK] = LoadSoundMem("data/sound/se_kick.wav");
	SEs[SE_MARIODIE] = LoadSoundMem("data/sound/se_mariodie.wav");
	SEs[SE_PIPE] = LoadSoundMem("data/sound/se_pipe.wav");
	SEs[SE_POWERUP] = LoadSoundMem("data/sound/se_powerup.wav");
	SEs[SE_POWERUP_APPEARS] = LoadSoundMem("data/sound/se_powerup_appears.wav");
	SEs[SE_STAGE_CLEAR] = LoadSoundMem("data/sound/se_stage_clear.wav");
	SEs[SE_STOMP] = LoadSoundMem("data/sound/se_stomp.wav");
	SEs[SE_WARNING] = LoadSoundMem("data/sound/se_warning.wav");
	SEs[SE_WORLD_CLEAR] = LoadSoundMem("data/sound/se_world_clear.wav");
	//---------------------------------------------------------
	ChangeVolumeSoundMem(255, SEs[SE_1UP]);
	ChangeVolumeSoundMem(250, SEs[SE_BOWSERFALLS]);
	ChangeVolumeSoundMem(220, SEs[SE_BOWSERFIRE]);
	ChangeVolumeSoundMem(255, SEs[SE_BREAKBLOCK]);
	ChangeVolumeSoundMem(255, SEs[SE_BUMP]);
	ChangeVolumeSoundMem(170, SEs[SE_COIN]);
	ChangeVolumeSoundMem(170, SEs[SE_FIREBALL]);
	ChangeVolumeSoundMem(170, SEs[SE_FIREWORKS]);
	ChangeVolumeSoundMem(255, SEs[SE_FLAGPOLE]);
	ChangeVolumeSoundMem(255, SEs[SE_GAME_OVER]);
	ChangeVolumeSoundMem(200, SEs[SE_JUMP_SMALL]);
	ChangeVolumeSoundMem(200, SEs[SE_JUMP_SUPER]);
	ChangeVolumeSoundMem(255, SEs[SE_KICK]);
	ChangeVolumeSoundMem(255, SEs[SE_MARIODIE]);
	ChangeVolumeSoundMem(255, SEs[SE_PIPE]);
	ChangeVolumeSoundMem(255, SEs[SE_POWERUP]);
	ChangeVolumeSoundMem(255, SEs[SE_POWERUP_APPEARS]);
	ChangeVolumeSoundMem(255, SEs[SE_STAGE_CLEAR]);
	ChangeVolumeSoundMem(255, SEs[SE_STOMP]);
	ChangeVolumeSoundMem(255, SEs[SE_WARNING]);
	ChangeVolumeSoundMem(255, SEs[SE_WORLD_CLEAR]);

	//---------------------------------------------------------
	//	音声のハンドルを入れる配列を初期化
	for (int i = 0; i < BGM_MAX; i++) {
		BGMs[i] = -1;
	}
	//---------------------------------------------------------
	BGMs[BGM_GROUND] = LoadMusicMem("data/sound/Ground_Theme.mp3");
	BGMs[BGM_UNDERGROUND] = LoadMusicMem("data/sound/Underground_Theme.mp3");
	BGMs[BGM_CASTLE] = LoadMusicMem("data/sound/Castle_Theme.mp3");
	//---------------------------------------------------------
	SetVolumeMusicMem(255,BGMs[BGM_GROUND]);
	SetVolumeMusicMem(255,BGMs[BGM_UNDERGROUND]);
	SetVolumeMusicMem(255,BGMs[BGM_CASTLE]);
}

SoundManager::~SoundManager()
{
	//	効果音のハンドルを解放
	for (int i = 0; i < SE_MAX; i++) {
		DeleteSoundMem(SEs[i]);
		SEs[i] = -1;
	}
	//	音声のハンドルを解放
	for (int i = 0; i < BGM_MAX; i++) {
		DeleteSoundMem(BGMs[i]);
		BGMs[i] = -1;
	}
}

void SoundManager::StopAllBGM(){
	for (int i = 0; i < BGM_MAX; i++) {
		if (BGMs[i] != -1) {
			StopMusicMem(BGMs[i]);
		}
	}
}

void SoundManager::PlayBGM(int BGMnum)
{
	if (BGMnum < 0 || BGMnum >= BGM_MAX) return;
	StopAllBGM();
	PlayMusicMem(BGMs[BGMnum], DX_PLAYTYPE_LOOP);
}

void SoundManager::PlaySE(int SEnum)
{
	if (SEnum < 0 || SEnum >= SE_MAX) return;
	PlaySoundMem(SEs[SEnum], DX_PLAYTYPE_BACK);
}
