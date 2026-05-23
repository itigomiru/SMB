#include "EnemySpawner.h"
#include "SceneManager.h"

EnemySpawner::EnemySpawner()
{

}
void EnemySpawner::SetObjectManager(ObjectManager* om)
{
	objectManager = om;
}

void EnemySpawner::SetSpawner()
{
	SpawnData data1 = { GOOMBA, 200.0f, 200.0f, false, true };
	SpawnData data2 = { KOOPA_TROOPA, 400.0f, 200.0f, false, true };
	SpawnData data3 = { PIRANHA_PLANT, 600.0f, 200.0f, false, true };
	spawnDataList.push_back(data1);
	spawnDataList.push_back(data2);
	spawnDataList.push_back(data3);
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
                //auto goomba =
                //    std::make_unique<Goomba>();

                //goomba->SetPosition(
                //    data.x,
                //    data.y);

                //enemy = std::move(goomba);

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