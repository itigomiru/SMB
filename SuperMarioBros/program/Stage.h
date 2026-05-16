#pragma once

enum stage_states
{
	STAGE_READY,
	STAGE_PLAYING,
	STAGE_CLEAR,
	STAGE_GAMEOVER,
};

int GetStageScore();
void AddStageScore(int point);

//	ステージで使う関数の宣言
void StageInit();
void StageUpdate();
void StageRender();
void StageExit();

