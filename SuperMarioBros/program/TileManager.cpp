#include "TileManager.h"

void TileManager::SetTile()
{
	std::vector<std::vector<int>> map1 = {
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	};
	maps.push_back(map1);
	currentStage = 0;
}