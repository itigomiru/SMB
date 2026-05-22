#include "TileManager.h"
#include "SceneManager.h"
#include "DxLib.h"
void TileManager::SetTile()
{
    std::vector<std::vector<int>> map1 =
    {
        { 1,0,0,0,0,0,0,0,0,0 },
        { 0,1,0,0,0,0,0,0,0,0 },
        { 0,0,1,0,0,0,0,0,0,0 },
        { 0,0,0,1,0,0,0,0,0,0 },
        { 0,0,0,0,1,0,0,0,0,0 },
        { 0,0,0,0,0,1,0,0,0,0 },
        { 0,0,0,0,0,0,1,0,0,0 },
        { 0,0,0,0,0,0,0,1,0,0 },
        { 0,0,0,0,0,0,0,0,1,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,0,0,0,0 },
        { 0,0,0,0,0,0,1,0,0,0 },
        { 0,0,0,0,0,1,0,0,0,0 },
        { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
    };

    map.resize(map1.size());

    for (int y = 0; y < map1.size(); y++)
    {
        map[y].resize(map1[y].size());

        for (int x = 0; x < map1[y].size(); x++)
        {
            map[y][x].type = map1[y][x];

            map[y][x].position =
            {
                static_cast<float>(x * 16),
                static_cast<float>(y * 16)
            };
        }
    }
}


void TileManager::Render(float cameraX) {
    for (int y = 0; y < map.size(); y++)
    {
        for (int x = 0; x < map[y].size(); x++)
        {
            int type = map[y][x].type;

            int drawX = (static_cast<int>(map[y][x].position.x) - static_cast<int>(cameraX)) * 3;
            int drawY = static_cast<int>(map[y][x].position.y) * 3;

            switch (type)
            {
            case TILE_EMPTY:
                break;

            case TILE_GROUND:
                DrawBox(
                    drawX,
                    drawY,
                    drawX + TILE_SIZE * 3,
                    drawY + TILE_SIZE * 3,
                    GetColor(255, 0, 0),
                    true);
                break;
            }
        }
    }
}

bool TileManager::IsSolid(int x, int y)
{
    if (y < 0 || y >= map.size())
        return false;

    if (x < 0 || x >= map[y].size())
        return false;

    return map[y][x].type == TILE_GROUND;
}