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
#include "Item.h"
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
	tileManager.SetObjectManager(&objectManager);
	enemySpawner.SetSpawner();
}

void Stage::Update()
{
   objectManager.Update(cameraX);
   enemySpawner.Update(cameraX);
   tileManager.Update();

   for (const auto& obj : objectManager.GetObjects())
   {
       // 相手が「敵（OT_ENEMY）」であり、まだ死んでいない場合のみ処理
       if (obj->objectType == Object::OT_ENEMY && !obj->isDead)
       {
           Enemy* enemy = static_cast<Enemy*>(obj.get());

		   if(enemy)
		   {
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
       if (obj->objectType == Object::OT_ITEM && !obj->isDead)
       {
           Item* item = static_cast<Item*>(obj.get());

           if (item && item->state == Item::IS_MOVING)
           {
               if (objectManager.HitObjects(player, item))
               {
                   switch (item->itemType)
                   {
                   case TileManager::ITEM_SUPERMASHROOM:
						   player->GetSuperMashroom();
						   break;
				   case TileManager::ITEM_1UPMASHROOM:
                       //player->Get1UPMashroom();
                       break;
                   case TileManager::ITEM_FIREFLOWER:
					   player->GetFireFlower();
                       break;
                   }
				   item->isDead = true; // アイテムを消す
               }
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
    DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(132, 134, 225), true);
    objectManager.Render(Object::RL_UNDER_TILE, cameraX);
    tileManager.Render(cameraX);
    objectManager.Render(Object::RL_ENEMY,cameraX);
    objectManager.Render(Object::RL_PLAYER,cameraX);
}
Stage::~Stage()
{

}
