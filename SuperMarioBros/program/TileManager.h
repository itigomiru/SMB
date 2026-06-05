#pragma once
#include "Float2.h"
#include <vector>

class ObjectManager;

struct Tile
{
	Float2 position;
	Float2 basePosition;
	float speedY;
	int type;
	bool breakable;
	int itemType;
};

class TileManager
{
private:
	std::vector<std::vector<Tile>> map;
	int currentStage;
	ObjectManager* objectManager;
	const float HIT_TILE_SPEED = 1.5f;

	int animationCounter = 0;    
	const int ANIM_SPEED = 12;      
	const int ANIM_FRAMES = 3;   

	bool isWait = false;
	int animWaitCounter = 0;
	const int ANIM_WAIT_TIME = 120;

	void AddPowerMash(Float2 pos);
	void Add1UPMash(Float2 pos);
	void AddFireFlower(Float2 pos);
	void AddStar(Float2 pos, int type);

public:
	enum ItemType {
		ITEM_NONE,
		ITEM_COIN,
		ITEM_POWERUP,
		ITEM_SUPERMASHROOM,
		ITEM_FIREFLOWER,
		ITEM_1UPMASHROOM,
		ITEM_STAR,
		ITEM_MAX
	};
	enum TileType {
		TILE_EMPTY				= 0,
		TILE_GROUND				= 1,
		TILE_BLOCK				= 2,
		TILE_QUESTION			= 3,
		TILE_PIPE_LEFT_TOP		= 4,
		TILE_PIPE_RIGHT_TOP		= 5,
		TILE_PIPE_LEFT_BOTTOM	= 6,
		TILE_PIPE_RIGHT_BOTTOM	= 7,
		TILE_HIDE_BLOCK			= 8,
		TILE_HITTED_BLOCK		= 9,
		TILE_STAIR_BLOCK        = 10,
		TILE_MAX
	};
	void SetTile();

	void Update();

	void Render(float cameraX);

	bool IsSolid(int x, int y);

	void HitTile(int x, int y,bool isPlayerSmall);

	void SetObjectManager(ObjectManager* manager) { objectManager = manager; }

	bool IsHidden(int x, int y);
};
