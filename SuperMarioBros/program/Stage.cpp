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
	if (UpdateFreeze())return;
	
	objectManager.Update(cameraX);
	enemySpawner.Update(cameraX);
	tileManager.Update();

	CheckHit();

	CameraUpdate();
}

void Stage::Render()
{
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(132, 134, 225), true);
	objectManager.Render(Object::RL_UNDER_TILE, cameraX);
	tileManager.Render(cameraX);
	objectManager.Render(Object::RL_ENEMY, cameraX);
	objectManager.Render(Object::RL_PLAYER, cameraX);
}
Stage::~Stage()
{

}

bool Stage::UpdateFreeze()
{
	if (player->isDead)
	{
		if (player->deathTimer > 0)
		{
			// 死亡アニメ、タイマー更新
			player->DeathUpdate();
		}
		else
		{
			if (player->stock > 1)
			{
				player->stock--;
				player->Init();
				cameraX = 0.0f;
				SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_TITLE);//debug
				//SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_PRESTAGE);
			}
			else;//SceneManager::GetInstance().ChangeScene(SceneManager::SCENE_GAMEOVER);
		}

		return true;
	}
	if (player->freezeTimer > 0)
	{
		player->PowerUpUpdate();
		return true;
	}
	if (player->invincibleTimer > 0)
	{
		player->invincibleTimer--;
		if (player->invincibleTimer > player->INVINCIBLE_FREEZE_TIME)return true;
	}

	return false;
}

void Stage::CameraUpdate()
{
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

void Stage::CheckHit()
{
	for (const auto& obj : objectManager.GetObjects())
	{
		// 相手が「敵（OT_ENEMY）」であり、まだ死んでいない場合のみ処理
		if (obj->objectType == Object::OT_ENEMY && !obj->isDead)
		{
			Enemy* enemy = static_cast<Enemy*>(obj.get());

			if (enemy)
			{
				if (objectManager.HitObjects(player, enemy))
				{

					// 踏んだかどうか
					if (player->CheckSquashEnemy(enemy))
					{
						enemy->OnSquashed();
					}
					else
					{
						player->Damage();
					}
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
						player->Get1UpMushroom();
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
	CheckHitFireballandEnemy();

}

void Stage::CheckHitFireballandEnemy()
{
    for (const auto& fireObj : objectManager.GetObjects())
    {
        if (fireObj->objectType != Object::OT_FIREBALL)continue;

        for (const auto& enemyObj : objectManager.GetObjects())
        {
            if (enemyObj->objectType != Object::OT_ENEMY)continue;

            if (enemyObj->isDead)continue;

            if (objectManager.HitObjects(fireObj.get(),enemyObj.get()))
            {
                Enemy* enemy = static_cast<Enemy*>(enemyObj.get());

				enemy->Death();
				//enemyの死亡エフェクト
                fireObj->isDead = true;
				//fireballの消滅エフェクト
                break;
            }
        }
    }
}