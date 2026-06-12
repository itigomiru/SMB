#include "EnemySpawner.h"
#include "SceneManager.h"
#include "GoombaController.h"
#include "KoopaTroopaController.h"
#include "FirebarController.h"
#include "BowserController.h"
#include "TileManager.h"


EnemySpawner::EnemySpawner()
{

}
void EnemySpawner::SetObjectManager(ObjectManager* om)
{
	objectManager = om;
}

void EnemySpawner::SetTileManager(TileManager* tm)
{
	tileManager = tm;
}


void EnemySpawner::SetSpawner() {
	spawnDataList.clear();
#include "SpawnData.inc"
}

void EnemySpawner::Update(float cameraX)
{
	for (auto& data : spawnDataList)
	{
		if (data.spawned)
		{
			continue;
		}

		// 画面右側に近づいたら出現
		if (data.x < cameraX + SCREEN_W + ENEMY_SPAWN_OFFSET)
		{
			std::unique_ptr<Object> enemy;

			switch (data.type)
			{
			case GOOMBA:
			{
				auto goomba = std::make_unique<Goomba>();

				goomba->SetPosition(data.x, data.y);
				goomba->SetTileManager(tileManager);
				enemy = std::move(goomba);

				break;
			}

			case KOOPA_TROOPA:
			{

				auto koopatroopa = std::make_unique<KoopaTroopa>();

				koopatroopa->SetPosition(data.x, data.y);
				koopatroopa->SetTileManager(tileManager);
				enemy = std::move(koopatroopa);

				break;
			}
			case FIREBAR:
			{
				int fireCount = 6;
				bool isClockwise = true;

				for (int i = 0; i < fireCount; i++)
				{
					float distance = i * 8.0f;

					float tileX = data.x / TILE_SIZE;
					float tileY = data.y / TILE_SIZE;

					auto fireballElement = std::make_unique<Firebar>(tileX, tileY, distance, isClockwise, tileManager);

					objectManager->AddObject(std::move(fireballElement));
				}

				data.spawned = true;
				break;
			}
			case PIRANHA_PLANT:
				break;

			case BOWSER:
			{
				auto bowser = std::make_unique<Bowser>(
					data.x,
					data.y,
					data.x - 64.0f, // 左移動制限
					data.x + 64.0f  // 右移動制限
				);

				bowser->SetTileManager(tileManager);
				bowser->SetObjectManager(objectManager);
				bowser->SetPlayer(player);

				enemy = std::move(bowser);

				break;
			}
			}
			if (enemy)
			{
				objectManager->AddObject(
					std::move(enemy));

				data.spawned = true;
			}
			
		}

	}

}