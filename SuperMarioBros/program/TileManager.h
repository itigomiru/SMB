#pragma once
#include "Float2.h"
#include <vector>

struct Tile
{
    Float2 position;
    int type;
	bool breakable;
	int itemType;
};

class TileManager
{
private:
    std::vector<std::vector<Tile>> map;
	int currentStage;

public:
	enum ItemType {
		ITEM_NONE,
		ITEM_COIN,
		ITEM_POWERUP,
		ITEM_MAX
	};
    enum TileType {
        TILE_EMPTY				= 0,
		TILE_GROUND				= 1,
        TILE_BLOCK				= 2,
		TILE_QUESTION			= 3,
		TILE_PIPE_LEFT_TOP		= 4,
		TILE_PIPE_RIGHT_TOP		= 5,
		TILE_PIPE_LEFT_Bottom	= 6,
		TILE_PIPE_RIGHT_Bottom	= 7,

		TILE_MAX
	};
    void SetTile();

    void Render(float cameraX);

    int GetTile(int x, int y);

    bool IsSolid(int x, int y);


};