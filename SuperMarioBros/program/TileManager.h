#pragma once
#include "Float2.h"
#include <vector>

struct Tile
{
    Float2 position;
    int type;
};

class TileManager
{
private:
    std::vector<std::vector<Tile>> map;
	int currentStage;

public:
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