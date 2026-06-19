#pragma once
#include "Scene.h"
#include "ObjectManager.h"
#include "TileManager.h"
#include "EnemySpawner.h"
#include "SoundManager.h"
#include "Player.h"

class Stage : public Scene
{
private :
	//	ステージに必要な変数を宣言
	ObjectManager objectManager;
	TileManager tileManager;
	EnemySpawner enemySpawner;
	Player* player = nullptr;
	int state;
	bool isPausing;
	int pauseTimer;
	const int PAUSE_TIME = 60;
	enum StageState
	{
		ST_NORMAL,
		ST_CLEAR,
		ST_DEATH,
	};
	Float2 playerStartPos;
	bool UpdateFreeze();
	void CameraUpdate();
	void CheckHit();
	void CheckHitFireballAndEnemy();
	void CheckHitShellAndEnemy();
	void CheckHitEnemyAndEnemy();
	void SetLift();
	void CheckHitPlayerAndLiftSide();

	int roadBreathTimer;
	const float ROAD_BREATH_COOL_TIME = 150;

public:
	Stage(int num = 0);
	void Init() override;
	void Update() override;
	void Render() override;
	~Stage() override;

	float cameraX = 0.0f;

	
};
