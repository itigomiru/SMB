#pragma once
#include <vector>

class TileManager
{
private:
    std::vector<std::vector<std::vector<int>>> maps;
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

    void Render();

    int GetTile(int x, int y);

    bool IsSolid(int x, int y);
};