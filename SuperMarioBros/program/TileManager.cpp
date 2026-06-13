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
#include "SoundManager.h"
#include"ImageManager.h"
#include "Coin.h"
#include "PlayerData.h"
#include <memory>
void TileManager::SetTile()
{
#include "StageData.inc"
	switch (currentStage)
	{
	case 0:
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
		break;
	case 1:
		map.resize(map4.size());

		for (int y = 0; y < map4.size(); y++)
		{
			map[y].resize(map4[y].size());
		}
#include "ItemData.inc"
		for (int y = 0; y < map4.size(); y++)
		{

			for (int x = 0; x < map4[y].size(); x++)
			{
				map[y][x].type = map4[y][x];

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
		break;
	case 2:
		map.resize(map_underground.size());
		for (int y = 0; y < map_underground.size(); y++)
		{
			map[y].resize(map_underground[y].size());

			for (int x = 0; x < map_underground[y].size(); x++)
			{
				map[y][x].type = map_underground[y][x];

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

		objectManager->AddObject(std::make_unique<Coin>(80, 80));
		objectManager->AddObject(std::make_unique<Coin>(96, 80));
		objectManager->AddObject(std::make_unique<Coin>(112, 80));
		objectManager->AddObject(std::make_unique<Coin>(128, 80));
		objectManager->AddObject(std::make_unique<Coin>(144, 80));

		objectManager->AddObject(std::make_unique<Coin>(64, 112));
		objectManager->AddObject(std::make_unique<Coin>(80, 112));
		objectManager->AddObject(std::make_unique<Coin>(96, 112));
		objectManager->AddObject(std::make_unique<Coin>(112, 112));
		objectManager->AddObject(std::make_unique<Coin>(128, 112));
		objectManager->AddObject(std::make_unique<Coin>(144, 112));
		objectManager->AddObject(std::make_unique<Coin>(160, 112));

		objectManager->AddObject(std::make_unique<Coin>(64, 144));
		objectManager->AddObject(std::make_unique<Coin>(80, 144));
		objectManager->AddObject(std::make_unique<Coin>(96, 144));
		objectManager->AddObject(std::make_unique<Coin>(112, 144));
		objectManager->AddObject(std::make_unique<Coin>(128, 144));
		objectManager->AddObject(std::make_unique<Coin>(144, 144));
		objectManager->AddObject(std::make_unique<Coin>(160, 144));

		break;
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
			int imgHandle = -1;
			switch (type)
			{
			case TILE_EMPTY:
				break;

			case TILE_GROUND:
				if (currentStage == 0)imgHandle = ImageManager::GetInstance().GetImage(IMAGE_GROUND);
				if (currentStage == 1)imgHandle = ImageManager::GetInstance().GetImage(IMAGE_CASTLE_GROUND);
				if (currentStage == 2)imgHandle = ImageManager::GetInstance().GetImage(IMAGE_UNDERGROUND);
				DrawGraph(drawX, drawY, imgHandle, true);
				break;
			case TILE_BLOCK:
				if (currentStage == 0)imgHandle = ImageManager::GetInstance().GetImage(IMAGE_BLOCK);
				if (currentStage == 1)imgHandle = ImageManager::GetInstance().GetImage(IMAGE_CASTLE_BLOCK);
				if (currentStage == 2)imgHandle = ImageManager::GetInstance().GetImage(IMAGE_UNDERGROUND_BLOCK);
				DrawGraph(drawX, drawY, imgHandle, true);
				break;
			case TILE_QUESTION:
				if (currentStage == 0)imgHandle = ImageManager::GetInstance().GetImage(IMAGE_QUESTION_BLOCK);
				if (currentStage == 1)imgHandle = ImageManager::GetInstance().GetImage(IMAGE_CASTLE_QUESTION_BLOCK);
				DrawRectGraph(drawX, drawY, srcX, 0, TILE_SIZE, TILE_SIZE, imgHandle, true, false);
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
				if (currentStage == 0)imgHandle = ImageManager::GetInstance().GetImage(IMAGE_HITTED_BLOCK);
				if (currentStage == 1)imgHandle = ImageManager::GetInstance().GetImage(IMAGE_CASTLE_HITTED_BLOCK);
				DrawGraph(drawX, drawY, imgHandle, true);
				break;
			case TILE_STAIR_BLOCK:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_STAIR_BLOCK), true);
				break;
			case TILE_PIPE_LEFT_TOP2:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_PIPE_LEFT_TOP_UNDERGROUND), true);
				break;
			case TILE_PIPE_LEFT_BOTTOM2:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_PIPE_LEFT_BOTTOM_UNDERGROUND), true);
				break;
			case TILE_PIPE_TOP2:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_PIPE_TOP_UNDERGROUND), true);
				break;
			case TILE_PIPE_BOTTOM2:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_PIPE_BOTTOM_UNDERGROUND), true);
				break;
			case TILE_PIPE_RIGHT_TOP2:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_PIPE_RIGHT_TOP_UNDERGROUND), true);
				break;
			case TILE_PIPE_RIGHT_BOTTOM2:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_PIPE_RIGHT_BOTTOM_UNDERGROUND), true);
				break;
			case TILE_CASTLE_BRIDGE:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_CASTLE_BRIDGE), true);
				break;
			case TILE_MAGMA_TOP:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_MAGMA_TOP), true);
				break;
			case TILE_MAGMA_BOTTOM:
				DrawGraph(drawX, drawY, ImageManager::GetInstance().GetImage(IMAGE_MAGMA_BOTTOM), true);
				break;
			}
		}
	}
	if (currentStage == 1)DrawGraph(2432 - static_cast<int>(cameraX), 184, ImageManager::GetInstance().GetImage(IMAGE_PRINCESS), true);
}

bool TileManager::IsSolid(int x, int y)
{
	if (y < 0 || y >= map.size())
		return false;

	if (x < 0 || x >= map[y].size())
		return false;

	return (map[y][x].type != TILE_EMPTY && map[y][x].type != TILE_HIDE_BLOCK && map[y][x].type != TILE_MAGMA_TOP && map[y][x].type != TILE_MAGMA_BOTTOM);
}

void TileManager::HitTile(int x, int y, bool isPlayerSmall)
{
	SoundManager::GetInstance().PlaySE(SoundManager::SE_BUMP);
	// 範囲外チェック（安全のため）
	if (y < 0 || y >= map.size() || x < 0 || x >= map[y].size()) return;

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

						enemy->Death(enemy->speed.x > 0.0f, 0);
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
		EffectManager::GetInstance().AddEffect(std::make_unique<BrockBreakEffect>(map[y][x].basePosition.x + (TILE_SIZE * 0.5), map[y][x].basePosition.y + (TILE_SIZE * 0.5)));
		SoundManager::GetInstance().PlaySE(SoundManager::SE_BREAKBLOCK);
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
			EffectManager::GetInstance().AddEffect(std::make_unique<CoinEffect>(map[y][x].basePosition.x + 4, map[y][x].basePosition.y));
			PlayerData::GetInstance().AddCoin(1);
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

	SoundManager::GetInstance().PlaySE(SoundManager::SE_POWERUP_APPEARS);
	objectManager->AddObject(std::move(mash));
}
void TileManager::Add1UPMash(Float2 pos)
{
	//mashを出す
	auto mash = std::make_unique<Mashroom>(pos.x, pos.y, ITEM_1UPMASHROOM);
	mash->SetTileManager(this);
	
	SoundManager::GetInstance().PlaySE(SoundManager::SE_POWERUP_APPEARS);
	objectManager->AddObject(std::move(mash));
}
void TileManager::AddFireFlower(Float2 pos)
{
	//fireflowerを出す
	auto flower = std::make_unique<FireFlower>(pos.x, pos.y, ITEM_FIREFLOWER);
	flower->SetTileManager(this);
	SoundManager::GetInstance().PlaySE(SoundManager::SE_POWERUP_APPEARS);
	objectManager->AddObject(std::move(flower));
}
void TileManager::AddStar(Float2 pos)
{
	//starを出す
	auto star = std::make_unique<Star>(pos.x, pos.y, ITEM_STAR);
	star->SetTileManager(this);
	SoundManager::GetInstance().PlaySE(SoundManager::SE_POWERUP_APPEARS);
	objectManager->AddObject(std::move(star));
}

bool TileManager::IsHidden(int x, int y) {
	if (y < 0 || y >= map.size()) return false;
	if (x < 0 || x >= map[y].size()) return false;

	return map[y][x].type == TILE_HIDE_BLOCK;
}
void TileManager::ChangeStage(int stageId)
{
	currentStage = stageId;
	SetTile();


	//objectManager->AllClear();
}

void TileManager::CollapseBridge(int num)
{
	if (currentStage != 1) return;
	SoundManager::GetInstance().PlaySE(SoundManager::SE_BREAKBLOCK);
	map[BRIDGE_Y][BRIDGE_RIGHT - num].type = TILE_EMPTY;
	bridgeTimer = 0;
	if (map[BRIDGE_Y][BRIDGE_LEFT].type == TILE_EMPTY)
	{
		bridgeState = BS_COLLAPSED;
	}
}