#include "Main.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Float2.h"
#include "Hit.h"
#include "ObjectManager.h"
#include "Player.h"
#include"ImageManager.h"
#include "EffectManager.h"
#include "Stage.h"
#include "TileManager.h"
#include "EnemySpawner.h"
#include "Enemy.h"

void Stage::Init()
{
	auto p = std::make_unique<Player>();
	player = p.get();
	player->SetTileManager(&tileManager);
	player->SetObjectManager(&objectManager);
	objectManager.AddObject(std::move(p));
	enemySpawner.SetObjectManager(&objectManager);
	enemySpawner.SetTileManager(&tileManager);

	tileManager.SetTile();
	enemySpawner.SetSpawner();
}

void Stage::Update()
{
   objectManager.Update(cameraX);
   enemySpawner.Update(cameraX);

   for (const auto& obj : objectManager.GetObjects())
   {
       // 相手が「敵（OT_ENEMY）」であり、まだ死んでいない場合のみ処理
       if (obj->objectType == Object::OT_ENEMY && !obj->isDead)
       {
           Enemy* enemy = dynamic_cast<Enemy*>(obj.get()); // Use dynamic_cast with obj.get()

            // 踏んだかどうか
            if (player->CheckSquashEnemy(enemy))
            {
                enemy->OnSquashed();
            }
            else
            {
                // 横から衝突した時の判定
            }
        }
    }


   float targetX = player->pos.x - 128;

   // 右に進む時だけ更新
   if (targetX > cameraX)
   {
       cameraX = targetX;
   }

   // 左端制限
   if (cameraX < 0)
   {
       cameraX = 0;
   }

   if (player->pos.x - cameraX < 0)
   {
       player->pos.x = cameraX;
       player->speed.x = 0.0f;
   }
}

void Stage::Render()
{
    tileManager.Render(cameraX);
    objectManager.Render(cameraX);
}
Stage::~Stage()
{

}