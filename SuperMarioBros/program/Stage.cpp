#include "Main.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Float2.h"
#include "Hit.h"
#include "LauncherController.h"
#include "GlidManager.h"
#include "BallController.h"
#include "NextManager.h"
#include"ImageManager.h"
#include "EffectManager.h"
#include "SoundManager.h"

int stage_state;
int stageNum = 0;
int counter = 0;
bool isGameOverStarted = false;
int gameOverDelayTimer = 0;
bool isGoSoundPlayed = false;
int stageScore = 0;
int oneStageScore = 0;
static constexpr int GAMEOVER_RETRY_DELAY = 60;
static constexpr int STAR_BG_OFFSET = 1344;
int stageTimer = 0;
//=================================================================================
//	ステージの処理
//=================================================================================

BallController* ball = nullptr;
int starY[2] = { 672, -672};
//---------------------------------------------------------------------------------
//	初期化
//---------------------------------------------------------------------------------
void StageInit()
{
	if (ball != nullptr) {
		delete ball;
		ball = nullptr;
	}
	SoundManager::GetInstance().StopAllBGM();
	GlidManager::GetInstance().Init();
	GlidManager::GetInstance().SetGlid(stageNum);
	NextManager::GetInstance().Init();
	EffectManager::GetInstance().ClearAll();
	isGameOverStarted = false;
	gameOverDelayTimer = 0;
	stage_state = STAGE_READY;
	isGoSoundPlayed = false;
	if (24 < stageNum && stageNum < 27) {
		starY[0] = 672;
		starY[1] = -672;
	}
	stageTimer = 0;
	oneStageScore = 0;
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
int GetStageScore()
{
	return stageScore;
}

void AddStageScore(int point)
{
	stageScore += point;
}

static void DrawNumberRightAligned(int rightX, int y, int value)
{
	if (value < 0) {
		value = 0;
	}

	int digits[10];
	int digitCount = 0;
	do {
		digits[digitCount++] = value % 10;
		value /= 10;
	} while (value > 0 && digitCount < 10);

	int digitWidth = 16 * 2;
	int totalWidth = digitCount * digitWidth;
	int startX = rightX - totalWidth;
	for (int i = digitCount - 1; i >= 0; --i) {
		int index = digitCount - 1 - i;
		int drawX = startX + (index * digitWidth);
		DrawRectRotaGraph(drawX, y, digits[i] * 16, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_NUMBER), true);
	}
}

static int CalculateOneStageScore()
{
	int elapsedSeconds = stageTimer / 60;
	if (elapsedSeconds <= 5) {
		return 50000;
	}
	if (elapsedSeconds >= 60) {
		return 0;
	}
	float t = static_cast<float>(elapsedSeconds - 5) / 55.0f;
	return static_cast<int>(50000.0f * (1.0f - t));
}

void StageUpdate()
{
		bool isBallFlying = (ball != nullptr);
	switch (stage_state)
	{
	case STAGE_READY:
		//ready go!の演出を後で追加
	if (CheckMusicMem(SoundManager::GetInstance().GetBGM(BGM_STAGE)) == false)PlayMusicMem(SoundManager::GetInstance().GetBGM(BGM_STAGE), DX_PLAYTYPE_BACK);
		counter++;
		if (counter > 130)
		{
			counter = 0;
			stage_state = STAGE_PLAYING;
		}
		if(CheckSoundMem(SoundManager::GetInstance().GetSE(SE_READY)) == false)PlaySoundMem(SoundManager::GetInstance().GetSE(SE_READY), DX_PLAYTYPE_BACK);
		break;
	case STAGE_PLAYING:
		stageTimer++;
	if (CheckMusicMem(SoundManager::GetInstance().GetBGM(BGM_STAGE)) == false)PlayMusicMem(SoundManager::GetInstance().GetBGM(BGM_STAGE), DX_PLAYTYPE_BACK);
		if (isGoSoundPlayed == false )
		{
			PlaySoundMem(SoundManager::GetInstance().GetSE(SE_GO), DX_PLAYTYPE_BACK);
			isGoSoundPlayed = true;
		}
		GlidManager::GetInstance().Update(isBallFlying);
		LauncherController::GetInstance().Update();
		NextManager::GetInstance().Update();
		if (PushHitKey(KEY_INPUT_SPACE))
		{
			if (ball == nullptr) {
				int nextColor = NextManager::GetInstance().GetNextBallColor();
				ball = new BallController(nextColor);
				NextManager::GetInstance().onFire(); // 発射をネクストマネージャーに通知
				LauncherController::GetInstance().Onfire(); // 発射アニメーション開始
			}
		}
		if (ball != nullptr) {
			ball->Update();
			if (ball->GetBallState() == EMPTY) {
				delete ball;
				ball = nullptr;
			}
		}

		// クリア判定
		if (GlidManager::GetInstance().IsClear() || PushHitKey(KEY_INPUT_0)) {
			//scene_next = SCENE_RESULT;
			int elapsedSeconds = stageTimer / 60;
			if (elapsedSeconds <= 5) {
				oneStageScore = 50000;
			}
			else if (elapsedSeconds >= 60) {
				oneStageScore = 0;
			}
			else {
				float t = static_cast<float>(elapsedSeconds - 5) / 55.0f;
				oneStageScore = static_cast<int>(50000.0f * (1.0f - t));
			}
			stageScore += oneStageScore;
			stage_state = STAGE_CLEAR;
			SoundManager::GetInstance().StopAllBGM();
		}
		// ゲームオーバー判定
		else if (GlidManager::GetInstance().IsGameOver()) {
			//scene_next = SCENE_TITLE; // ゲームオーバー時はタイトル画面に戻す
			stage_state = STAGE_GAMEOVER;
		}

		break;
	case STAGE_CLEAR:
		//クリア演出を後で追加
		LauncherController::GetInstance().Update();
		NextManager::GetInstance().Update();
		if (CheckMusicMem(SoundManager::GetInstance().GetBGM(BGM_CLEAR)) == false)
			PlayMusicMem(SoundManager::GetInstance().GetBGM(BGM_CLEAR), DX_PLAYTYPE_BACK);
		counter++;
		if (counter > 164)
		{
			counter = 0;
			stageNum++;
			if (stageNum >= STAGE_MAX) {
				stageNum = 0;
				scene_next = SCENE_CLEAR;
			}
			StageInit();
		}
		break;
	case STAGE_GAMEOVER:
		if (!isGameOverStarted) {
			GlidManager::GetInstance().GameOver();
			isGameOverStarted = true;
			gameOverDelayTimer = 0;
		}
		GlidManager::GetInstance().Update(isBallFlying);
		LauncherController::GetInstance().Update();
		NextManager::GetInstance().Update();
		if (GlidManager::GetInstance().IsGameOverAnimationFinished()) {
			gameOverDelayTimer++;
			if (gameOverDelayTimer >= GAMEOVER_RETRY_DELAY) {
				StageInit();
			}
		}
		break;

	}
	EffectManager::GetInstance().Update();
	if (24 < stageNum && stageNum < 27)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int i = 0; i < 2; i++)
			{
				starY[i] += 1;
			}

			// 1枚目が下へ行き切った
			if (starY[0] >= STAR_BG_OFFSET)
			{
				starY[0] = starY[1] - STAR_BG_OFFSET;
			}

			// 2枚目が下へ行き切った
			if (starY[1] >= STAR_BG_OFFSET)
			{
				starY[1] = starY[0] - STAR_BG_OFFSET;
			}
		}
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void StageRender()
{

	if (stageNum < 3)
	{
	DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAGE1), true);
	DrawRectRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 - 30, GlidManager::GetInstance().deadLineRowOffset * 128, 0, 128, 162, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SHUTTER_STAGE1), true);
	DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 + 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WALL_STAGE1), true);
	}
	else if (stageNum < 6)
	{
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAGE2), true);
		DrawRectRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 - 30, GlidManager::GetInstance().deadLineRowOffset * 128, 0, 128, 162, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SHUTTER_STAGE2), true);
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 + 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WALL_STAGE2), true);
	}
	else if (stageNum < 9)
	{
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAGE3), true);
		DrawRectRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 - 30, GlidManager::GetInstance().deadLineRowOffset * 128, 0, 128, 162, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SHUTTER_STAGE3), true);
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 + 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WALL_STAGE3), true);
	}
	else if (stageNum < 12)
	{
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAGE4), true);
		DrawRectRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 - 30, GlidManager::GetInstance().deadLineRowOffset * 128, 0, 128, 162, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SHUTTER_STAGE4), true);
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 + 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WALL_STAGE4), true);
	}
	else if (stageNum < 15)
	{
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAGE5), true);
		DrawRectRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 - 30, GlidManager::GetInstance().deadLineRowOffset * 128, 0, 128, 162, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SHUTTER_STAGE5), true);
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 + 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WALL_STAGE5), true);
	}
	else if (stageNum < 18)
	{
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAGE6), true);
		DrawRectRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 - 30, GlidManager::GetInstance().deadLineRowOffset * 128, 0, 128, 162, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SHUTTER_STAGE6), true);
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 + 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WALL_STAGE6), true);
	}
	else if (stageNum < 21)
	{
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAGE7), true);
		DrawRectRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 - 30, GlidManager::GetInstance().deadLineRowOffset * 128, 0, 128, 162, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SHUTTER_STAGE7), true);
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 + 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WALL_STAGE7), true);
	}
	else if (stageNum < 24)
	{
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAGE8), true);
		DrawRectRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 - 30, GlidManager::GetInstance().deadLineRowOffset * 128, 0, 128, 162, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SHUTTER_STAGE8), true);
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 + 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WALL_STAGE8), true);
	}
	else if (stageNum < 27)
	{
		//STARRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR
		DrawRotaGraph(SCREEN_W * 0.5, starY[0], 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAR), true);
		DrawRotaGraph(SCREEN_W * 0.5, starY[1], 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAR), true);
		DrawRectRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 - 30, GlidManager::GetInstance().deadLineRowOffset * 128, 0, 128, 162, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAR_SHUTTER), true);
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 + 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAR_WALL), true);
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H - 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_GLASS), true);
	}
	else if (stageNum < 30)
	{
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_STAGE9), true);
		DrawRectRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 - 30, GlidManager::GetInstance().deadLineRowOffset * 128, 0, 128, 162, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SHUTTER_STAGE9), true);
		DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.5 + 8, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_WALL_STAGE9), true);
	}
	

	LauncherController::GetInstance().Render();
	GlidManager::GetInstance().Render();
	EffectManager::GetInstance().Render();
	NextManager::GetInstance().Render();
	if (ball != nullptr) {
		ball->Render();
	}
		int srcX_r = 16 * ((stageNum + 1) % 10);
		int srcX_l = 16 * ((stageNum + 1) / 10);
		switch (stage_state)
		{
		case STAGE_READY:
			DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.35, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_ROUNDBOARD), true);
			if (srcX_l != 0)DrawRectRotaGraph(SCREEN_W * 0.5 - 16, SCREEN_H * 0.35 + 16, srcX_l, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_NUMBER), true);
			DrawRectRotaGraph(SCREEN_W * 0.5 + 16, SCREEN_H * 0.35 + 16, srcX_r, 0, 16, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_NUMBER), true);
			break;
		case STAGE_CLEAR:
			if (counter < 82)DrawRotaGraph(SCREEN_W * 0.5, SCREEN_H * 0.35, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_ROUND_CLEAR), true);
			else
			{
				(SCREEN_W * 0.3f);
				(SCREEN_W * 0.3f);
				(SCREEN_H * 0.35f);
				(SCREEN_H * 0.65f);
				DrawRotaGraph(SCREEN_W * 0.7f, SCREEN_H * 0.35f, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SEC), true);
				DrawRotaGraph(SCREEN_W * 0.7f, SCREEN_H * 0.65f, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_PTS), true);
				DrawNumberRightAligned(SCREEN_W * 0.55f, SCREEN_H * 0.35f, stageTimer / 60);
				DrawNumberRightAligned(SCREEN_W * 0.55f, SCREEN_H * 0.65f, oneStageScore);
			}
		break;
	}

	int displayScore = stageScore;
	if (displayScore < 0) {
		displayScore = 0;
	}
	if (displayScore > 99999999) {
		displayScore = 99999999;
	}
	int scoreDigits[8];
	for (int i = 7; i >= 0; --i) {
		scoreDigits[i] = displayScore % 10;
		displayScore /= 10;
	}
	for (int i = 0; i < 8; ++i) {
		DrawRectRotaGraph(72 + (i * 16), 20, scoreDigits[i] * 8, 0, 8, 16, 2.0f, 0, ImageManager::GetInstance().GetImage(IMAGE_SCORE_NUMBER), true);
	}

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void StageExit()
{
}
