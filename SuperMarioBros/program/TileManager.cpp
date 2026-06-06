#include "TileManager.h"
#include "SceneManager.h"
#include "Mashroom.h"
#include "FireFlower.h"
#include "Enemy.h"
#include "DxLib.h"
#include "Star.h"
#include "EffectManager.h"
#include "CoinEffect.h"
#include "blockBreakEffect.h"
#include <memory>
#include"ImageManager.h"
void TileManager::SetTile()
{
	std::vector<std::vector<int>> map1 =
	{
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,2,2,2,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,2,3,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,2,3,2,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,5,0,0,0,0,0,0,0,0,0,4,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,2,0,0,0,0,3,0,0,3,0,0,3,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,10,0,0,10,0,0,0,0,0,0,0,0,0,0,10,10,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,2,2,3,2,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,10,0,10,0,0,0,0,0},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,5,0,0,0,0,0,0,6,7,0,0,0,0,0,0,0,0,0,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,0,0,10,10,0,0,0,0,0,0,0,0,10,10,10,0,0,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,10,0,0,0,0},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,5,0,0,0,0,0,0,0,0,6,7,0,0,0,0,0,0,6,7,0,0,0,0,0,0,0,0,0,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,0,0,10,10,10,0,0,0,0,0,0,10,10,10,10,0,0,10,10,10,0,0,0,0,0,4,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,5,0,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,10,0,0,0,10,0,0,0,0},
		{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,0,0,0,0,0,0,0,0,6,7,0,0,0,0,0,0,6,7,0,0,0,0,0,0,0,0,0,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,10,10,10,10,0,0,10,10,10,10,0,0,0,0,10,10,10,10,10,0,0,10,10,10,10,0,0,0,0,6,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,10,10,10,10,10,10,10,10,10,0,0,0,0,0,0,0,0,10,0,0,0,10,0,0,0,10,0,0,0,0},
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};

	map.resize(map1.size());

	for (int y = 0; y < map1.size(); y++)
	{
		map[y].resize(map1[y].size());
	}
#include "ItemData.inc"
	for (int y = 0; y < map1.size(); y++)
	{

		for (int x = 0; x < map1[y].size(); x++)
		{
			map[y][x].type = map1[y][x];

			map[y][x].basePosition =
			{
				static_cast<float>(x * TILE_SIZE),static_cast<float>(y * TILE_SIZE)
			};
			map[y][x].position = map[y][x].basePosition;

			map[y][x].speedY = 0.0f;

			if (map[y][x].type == TILE_BLOCK)
			{
				map[y][x].breakable = true;
				if (ItemType(map[y][x].itemType) != ITEM_NONE)
				{
					map[y][x].breakable = false;
				}
			}
		}
	}
}


void TileManager::Render(float cameraX) {

	int animFrame = animationCounter / ANIM_SPEED;

	int srcX = animFrame * TILE_SIZE;

	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[y].size(); x++)
		{
			int type = map[y][x].type;

			int drawX = (static_cast<int>(map[y][x].position.x) - static_cast<int>(cameraX));
			int drawY = static_cast<int>(map[y][x].position.y);
			switch (type)
			{
			case TILE_EMPTY:
				break;

			case TILE_GROUND:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_GROUND), true);
				break;
			case TILE_BLOCK:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_BLOCK), true);
				break;
			case TILE_QUESTION:
				DrawRectGraph(drawX, drawY, srcX, 0, TILE_SIZE, TILE_SIZE, ImageManager::GetInstance().GetImage(IMAGE_QUESTION_BLOCK), true, false);
				break;
			case TILE_PIPE_LEFT_TOP:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_PIPE_LEFT_TOP), true);
				break;
			case TILE_PIPE_RIGHT_TOP:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_PIPE_RIGHT_TOP), true);
				break;
			case TILE_PIPE_LEFT_BOTTOM:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_PIPE_LEFT_BOTTOM), true);
				break;
			case TILE_PIPE_RIGHT_BOTTOM:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_PIPE_RIGHT_BOTTOM), true);
				break;
			case TILE_HIDE_BLOCK:
				break;
			case TILE_HITTED_BLOCK:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_HITTED_BLOCK), true);
				break;
			case TILE_STAIR_BLOCK:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_STAIR_BLOCK), true);
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

	return (map[y][x].type != TILE_EMPTY && map[y][x].type != TILE_HIDE_BLOCK);
}

void TileManager::HitTile(int x, int y, bool isPlayerSmall)
{
	// 範囲外チェック（安全のため）
	if (y < 0 || y >= map.size() || x < 0 || x >= map[y].size()) return;

	// 叩かれたタイルの物理的な位置をピクセル換算（引数の x, y を使用するように修正）
	float blockLeft = x * TILE_SIZE;
	float blockRight = (x + 1) * TILE_SIZE;
	float blockTop = y * TILE_SIZE;
	if (objectManager == nullptr) return;
	auto checkAndHitEnemyAbove = [&]() {
		if (objectManager == nullptr) return;
		auto& objects = objectManager->GetObjects();

		for (auto& obj : objects)
		{
			if (obj && obj->objectType == Object::OT_ENEMY)
			{
				Enemy* enemy = static_cast<Enemy*>(obj.get());

				// エネミーの足元、左右の範囲を計算
				float enemyBottom = enemy->pos.y + enemy->size.h;
				float enemyLeft = enemy->pos.x;
				float enemyRight = enemy->pos.x + enemy->size.w;

				if (enemyBottom >= blockTop - 4.0f && enemyBottom <= blockTop + 2.0f)
				{
					if (enemyRight > blockLeft && enemyLeft < blockRight)
					{
						enemy->Death();
					}
				}
			}
		}
		};
	auto checkAndHitMashAbove = [&]() {
		if (objectManager == nullptr) return;
		auto& objects = objectManager->GetObjects();

		for (auto& obj : objects)
		{
			if (obj && obj->objectType == Object::OT_ITEM)
			{
				Item* mash = static_cast<Item*>(obj.get());

				// エネミーの足元、左右の範囲を計算
				float enemyBottom = mash->pos.y + mash->size.h;
				float enemyLeft = mash->pos.x;
				float enemyRight = mash->pos.x + mash->size.w;

				if (enemyBottom >= blockTop - 4.0f && enemyBottom <= blockTop + 2.0f)
				{
					if (enemyRight > blockLeft && enemyLeft < blockRight)
					{
						mash->speed.y -= HIT_ITEM_HOP_SPEED;
					}
				}
			}
		}
		};

	if (map[y][x].breakable && !isPlayerSmall)
	{

		checkAndHitEnemyAbove();
		checkAndHitMashAbove();
		EffectManager::GetInstance().AddEffect(std::make_unique<BrockBreakEffect>(map[y][x].basePosition.x, map[y][x].basePosition.y));

		map[y][x].type = TILE_EMPTY;
		return;
	}

	if (map[y][x].type == TILE_BLOCK || map[y][x].type == TILE_QUESTION)
	{
		map[y][x].speedY = -HIT_TILE_SPEED;


		checkAndHitEnemyAbove();
		checkAndHitMashAbove();

	}


	if (map[y][x].type == TILE_QUESTION || map[y][x].type == TILE_HIDE_BLOCK || (map[y][x].type == TILE_BLOCK && !map[y][x].breakable))
	{
		map[y][x].type = TILE_HITTED_BLOCK;

		switch (ItemType(map[y][x].itemType))
		{
		case ITEM_COIN:
			// コインを出す
			EffectManager::GetInstance().AddEffect(std::make_unique<CoinEffect>(map[y][x].basePosition.x + 4, map[y][x].basePosition.y));
			break;
		case ITEM_POWERUP:
			if (isPlayerSmall) AddPowerMash(map[y][x].basePosition);
			else               AddFireFlower(map[y][x].basePosition);
			break;
		case ITEM_1UPMASHROOM:
			Add1UPMash(map[y][x].basePosition);
			break;
		case ITEM_STAR:
			AddStar(map[y][x].basePosition);
			break;
		default:
			break;

		}
	}
}

void TileManager::Update()
{

	if (animWaitCounter > 0)
	{
		animWaitCounter--;
	}
	else
	{
		int prevFrame = animationCounter / ANIM_SPEED;
		animationCounter = (animationCounter + 1) % (ANIM_SPEED * ANIM_FRAMES);
		int nextFrame = animationCounter / ANIM_SPEED;

		if (prevFrame != 0 && nextFrame == 0)
		{
			animWaitCounter = ANIM_WAIT_TIME;
		}
	}
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[y].size(); x++)
		{
			if (map[y][x].type == TILE_BLOCK || map[y][x].type == TILE_QUESTION || map[y][x].type == TILE_HITTED_BLOCK)
			{
				map[y][x].position.y += map[y][x].speedY;
				map[y][x].speedY += SceneManager::GetInstance().GRAVITY / 2;
				if (map[y][x].position.y > map[y][x].basePosition.y)
				{
					map[y][x].position.y = map[y][x].basePosition.y;
					map[y][x].speedY = 0.0f;
				}
			}
		}
	}
}
void TileManager::AddPowerMash(Float2 pos)
{
	//mashを出す
	auto mash = std::make_unique<Mashroom>(pos.x, pos.y, ITEM_SUPERMASHROOM);
	mash->SetTileManager(this);

	objectManager->AddObject(std::move(mash));
}
void TileManager::Add1UPMash(Float2 pos)
{
	//mashを出す
	auto mash = std::make_unique<Mashroom>(pos.x, pos.y, ITEM_1UPMASHROOM);
	mash->SetTileManager(this);

	objectManager->AddObject(std::move(mash));
}
void TileManager::AddFireFlower(Float2 pos)
{
	//fireflowerを出す
	auto flower = std::make_unique<FireFlower>(pos.x, pos.y, ITEM_FIREFLOWER);
	flower->SetTileManager(this);
	objectManager->AddObject(std::move(flower));
}
void TileManager::AddStar(Float2 pos)
{
	//starを出す
	auto star = std::make_unique<Star>(pos.x, pos.y, ITEM_STAR);
	star->SetTileManager(this);
	objectManager->AddObject(std::move(star));
}

bool TileManager::IsHidden(int x, int y) {
	if (y < 0 || y >= map.size()) return false;
	if (x < 0 || x >= map[y].size()) return false;

	return map[y][x].type == TILE_HIDE_BLOCK;
}