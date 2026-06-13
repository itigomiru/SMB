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
	int currentStage = 0;
	ObjectManager* objectManager;
	const float HIT_TILE_SPEED = 1.5f;
	const float HIT_ITEM_HOP_SPEED = 5.0f;

	int animationCounter = 0;    
	const int ANIM_SPEED = 10;      
	const int ANIM_FRAMES = 3;   

	bool isWait = false;
	int animWaitCounter = 0;
	const int ANIM_WAIT_TIME = 20;

	void AddPowerMash(Float2 pos);
	void Add1UPMash(Float2 pos);
	void AddFireFlower(Float2 pos);
	void AddStar(Float2 pos);




public:
	const int BRIDGE_LEFT = 128;
	const int BRIDGE_RIGHT = 140;
	const int BRIDGE_Y = 10;
	const int BRIDGE_COLLAPSE_INTERVAL = 5;
	int bridgeNum = 0;
	int bridgeTimer = 0;
	int bridgeState = 0; // 0: 通常, 1: 崩壊中, 2: 崩壊後
	enum BridgeState
	{
		BS_NORMAL,
		BS_COLLAPSING,
		BS_COLLAPSED,
		BS_CLEAR,
	};
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
		TILE_PIPE_LEFT_TOP2		= 11,
		TILE_PIPE_LEFT_BOTTOM2	= 12,
		TILE_PIPE_TOP2			= 13,
		TILE_PIPE_BOTTOM2		= 14,
		TILE_PIPE_RIGHT_TOP2	= 15,
		TILE_PIPE_RIGHT_BOTTOM2 = 16,
		TILE_CASTLE_BRIDGE		= 17,
		TILE_MAGMA_TOP			= 18,
		TILE_MAGMA_BOTTOM		= 19,
		TILE_BLACK				= 20,
		TILE_MAX
	};
	void SetTile();

	void Update();

	void Render(float cameraX);

	bool IsSolid(int x, int y);

	void HitTile(int x, int y,bool isPlayerSmall);

	void SetObjectManager(ObjectManager* manager) { objectManager = manager; }

	bool IsHidden(int x, int y);

	int GetCurrentStage() const { return currentStage; }

	void ChangeStage(int stage);

	void SetCurrentStage(int stage) { currentStage = stage; }

	void CollapseBridge(int num);
};
