#include "EnemySpawner.h"
#include "SceneManager.h"
#include "GoombaController.h"
#include "KoopaTroopaController.h"
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

    spawnDataList = {
        { GOOMBA,          320.0f, 190.0f, false, true },
        { GOOMBA,          640.0f, 190.0f, false, true },
        { GOOMBA,          800.0f, 190.0f, false, true },
        { GOOMBA,          832.0f, 190.0f, false, true },
        { GOOMBA,         1280.0f,  62.0f, false, true },
        { GOOMBA,         1312.0f,  62.0f, false, true },
        { GOOMBA,         1552.0f, 190.0f, false, true },
        { GOOMBA,         1584.0f, 190.0f, false, true },
        { KOOPA_TROOPA,   1696.0f, 182.0f, false, true },
        { GOOMBA,         1840.0f, 190.0f, false, true },
        { GOOMBA,         1872.0f, 190.0f, false, true },
        { GOOMBA,         2016.0f, 190.0f, false, true },
        { GOOMBA,         2048.0f, 190.0f, false, true },
        { GOOMBA,         2096.0f, 190.0f, false, true },
        { GOOMBA,         2784.0f, 190.0f, false, true },
        { GOOMBA,         2816.0f, 190.0f, false, true }
    };
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