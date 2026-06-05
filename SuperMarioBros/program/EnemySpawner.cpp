#include "EnemySpawner.h"
#include "SceneManager.h"
#include "GoombaController.h"
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

void EnemySpawner::SetSpawner()
{
	SpawnData data1 = { GOOMBA, 320.0f, 190.0f, false, true };
	SpawnData data2 = { GOOMBA, 640.0f, 190.0f, false, true };
	SpawnData data3 = { GOOMBA, 800.0f, 190.0f, false, true };
	SpawnData data4 = { GOOMBA, 832.0f, 190.0f, false, true };
	SpawnData data5 = { GOOMBA, 1280.0f, 62.0f, false, true };
	SpawnData data6 = { GOOMBA, 1312.0f, 62.0f, false, true };
	SpawnData data7 = { GOOMBA, 1552.0f, 190.0f, false, true };
	SpawnData data8 = { GOOMBA, 1584.0f, 190.0f, false, true };
	SpawnData data9 = { KOOPA_TROOPA, 1696.0f, 190.0f, false, true };
    SpawnData data10 = { GOOMBA, 1840.0f, 190.0f, false, true };
    SpawnData data11 = { GOOMBA, 1872.0f, 190.0f, false, true };
    SpawnData data12 = { GOOMBA, 2016.0f, 190.0f, false, true };
    SpawnData data13 = { GOOMBA, 2048.0f, 190.0f, false, true };
    SpawnData data14 = { GOOMBA, 2096.0f, 190.0f, false, true };
    SpawnData data15 = { GOOMBA, 2784.0f, 190.0f, false, true };
    SpawnData data16 = { GOOMBA, 2816.0f, 190.0f, false, true };

	spawnDataList.push_back(data1);
	spawnDataList.push_back(data2);
	spawnDataList.push_back(data3);
	spawnDataList.push_back(data4);
	spawnDataList.push_back(data5);
	spawnDataList.push_back(data6);
	spawnDataList.push_back(data7);
	spawnDataList.push_back(data8);
	spawnDataList.push_back(data9);
	spawnDataList.push_back(data10);
	spawnDataList.push_back(data11);
	spawnDataList.push_back(data12);
	spawnDataList.push_back(data13);
	spawnDataList.push_back(data14);
	spawnDataList.push_back(data15);
	spawnDataList.push_back(data16);


}

void EnemySpawner::Update(float cameraX)
{
    for (auto& data : spawnDataList)
    {
        if (data.spawned)
        {
            continue;
        }

        // âÊñ âEë§Ç…ãﬂÇ√Ç¢ÇΩÇÁèoåª
        if (data.x < cameraX + SCREEN_W + 64)
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
                break;

            case PIRANHA_PLANT:
                break;

            case BOWSER:
                break;
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