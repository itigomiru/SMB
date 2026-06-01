#pragma once
#include "ObjectManager.h"
#include<vector>
class TileManager;

struct SpawnData
{
	int		type;		// 敵の種類
	float x;			// 出現位置X
	float y;			// 出現位置Y
	
	bool spawned;		// 出現したか

	bool lookRight;		// 右を向いているか
};

class EnemySpawner
{
private:
	std::vector<SpawnData> spawnDataList;	// 出現データのリスト
	ObjectManager* objectManager = nullptr;	
	TileManager* tileManager = nullptr;
	enum EnemyType
	{
		GOOMBA,
		KOOPA_TROOPA,
		PIRANHA_PLANT,
		BOWSER,

	};
public:
	EnemySpawner();
	void SetTileManager(TileManager* tm);
	void Update(float cameraX);
	void SetObjectManager(ObjectManager* om);
	void SetSpawner();
};