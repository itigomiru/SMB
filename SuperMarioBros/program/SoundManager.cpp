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
	//	音声のハンドルを入れる配列を初期化
	for (int i = 0; i < BGM_MAX; i++) {
		BGMs[i] = -1;
	}
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
