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
        TILE_EMPTY,
		TILE_GROUND,
        TILE_BLOCK,
		TILE_QUESTION,
		TILE_MAX
	};
    void SetTile();

    void Render(float cameraX);

    int GetTile(int x, int y);

    bool IsSolid(int x, int y);


};