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
	SEs[SE_JUMP_SMALL] = LoadSoundMem("data/sound/se_jump-small.wav");
	SEs[SE_JUMP_SUPER] = LoadSoundMem("data/sound/se_jump-super.wav");
	SEs[SE_KICK] = LoadSoundMem("data/sound/se_kick.wav");
	SEs[SE_PIPE] = LoadSoundMem("data/sound/se_pipe.wav");
	SEs[SE_POWERUP] = LoadSoundMem("data/sound/se_powerup.wav");
	SEs[SE_POWERUP_APPEARS] = LoadSoundMem("data/sound/se_powerup_appears.wav");
	SEs[SE_STOMP] = LoadSoundMem("data/sound/se_stomp.wav");
	//---------------------------------------------------------
	ChangeVolumeSoundMem(255, SEs[SE_1UP]);
	ChangeVolumeSoundMem(250, SEs[SE_BOWSERFALLS]);
	ChangeVolumeSoundMem(220, SEs[SE_BOWSERFIRE]);
	ChangeVolumeSoundMem(255, SEs[SE_BREAKBLOCK]);
	ChangeVolumeSoundMem(180, SEs[SE_BUMP]);
	ChangeVolumeSoundMem(170, SEs[SE_COIN]);
	ChangeVolumeSoundMem(170, SEs[SE_FIREBALL]);
	ChangeVolumeSoundMem(170, SEs[SE_FIREWORKS]);
	ChangeVolumeSoundMem(200, SEs[SE_JUMP_SMALL]);
	ChangeVolumeSoundMem(200, SEs[SE_JUMP_SUPER]);
	ChangeVolumeSoundMem(255, SEs[SE_KICK]);
	ChangeVolumeSoundMem(255, SEs[SE_PIPE]);
	ChangeVolumeSoundMem(255, SEs[SE_POWERUP]);
	ChangeVolumeSoundMem(255, SEs[SE_POWERUP_APPEARS]);
	ChangeVolumeSoundMem(255, SEs[SE_STOMP]);


	//---------------------------------------------------------
	//	音声のハンドルを入れる配列を初期化
	for (int i = 0; i < BGM_MAX; i++) {
		BGMs[i] = -1;
	}
	//---------------------------------------------------------
	BGMs[BGM_GROUND]		= LoadSoundMem("data/sound/Ground_Theme.mp3");
	BGMs[BGM_UNDERGROUND]	= LoadSoundMem("data/sound/Underground_Theme.mp3");
	BGMs[BGM_CASTLE]		= LoadSoundMem("data/sound/Castle_Theme.mp3");
	BGMs[BGM_STAGE_CLEAR]	= LoadSoundMem("data/sound/se_stage_clear.wav");
	BGMs[BGM_FLAGPOLE]		= LoadSoundMem("data/sound/se_flagpole.wav");
	BGMs[BGM_WORLD_CLEAR]	= LoadSoundMem("data/sound/se_world_clear.wav");
	BGMs[BGM_GAME_OVER]		= LoadSoundMem("data/sound/se_gameover.wav");
	BGMs[BGM_MARIODIE]		= LoadSoundMem("data/sound/se_mariodie.wav");
	BGMs[BGM_STAR]			= LoadSoundMem("data/sound/bgm_star.mp3");
	BGMs[BGM_WARNING] = LoadSoundMem("data/sound/se_warning.wav");
	BGMs[BGM_HR_GROUND] = LoadSoundMem("data/sound/hrGround_Theme.mp3");
	BGMs[BGM_HR_UNDERGROUND] = LoadSoundMem("data/sound/hrUnderground_Theme.mp3");
	BGMs[BGM_HR_CASTLE] = LoadSoundMem("data/sound/hrCastle_Theme.mp3");
	BGMs[BGM_HR_STAR] = LoadSoundMem("data/sound/hrbgm_star.mp3");
	//---------------------------------------------------------
	ChangeVolumeSoundMem(255,BGMs[BGM_GROUND]);
	ChangeVolumeSoundMem(255,BGMs[BGM_UNDERGROUND]);
	ChangeVolumeSoundMem(255,BGMs[BGM_CASTLE]);
	ChangeVolumeSoundMem(180, BGMs[BGM_WORLD_CLEAR]);
	ChangeVolumeSoundMem(255, BGMs[BGM_WARNING]);
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
			StopSoundMem(BGMs[i]);
		}
	}
}

void SoundManager::PlayBGM(int BGMnum)
{
	if (BGMnum < 0 || BGMnum >= BGM_MAX) return;
	StopAllBGM();
	PlaySoundMem(BGMs[BGMnum], DX_PLAYTYPE_LOOP);
}
void SoundManager::PlayShotBGM(int BGMnum)
{
	if (BGMnum < 0 || BGMnum >= BGM_MAX) return;
	StopAllBGM();
	PlaySoundMem(BGMs[BGMnum], DX_PLAYTYPE_BACK);
}

void SoundManager::PlaySE(int SEnum)
{
	if (SEnum < 0 || SEnum >= SE_MAX) return;
	PlaySoundMem(SEs[SEnum], DX_PLAYTYPE_BACK);
}
