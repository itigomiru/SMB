#include "Main.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Float2.h"
#include "Fireball.h"
#include "ObjectManager.h"
#include "Player.h"
#include"ImageManager.h"
#include "EffectManager.h"
#include "Stage.h"
#include "Item.h"
#include "TileManager.h"
#include "EnemySpawner.h"
#include "PlayerData.h"
#include "Enemy.h"
#include "Object.h"
#include "KoopaTroopaController.h"
#include "Goal.h"

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
	objectManager.AddObject(std::make_unique<Goal>());
}

void Stage::Update()
{
	if (UpdateFreeze())return;
	CameraUpdate();

	objectManager.Update(cameraX);
	enemySpawner.Update(cameraX);
	tileManager.Update();
	EffectManager::GetInstance().Update();

	CheckHit();

}

void Stage::Render()
{
	DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(132, 134, 225), true);
	for (int i = 0; i < 5; i++)
	{
		DrawGraph(i * 768 - static_cast<int>(cameraX), TILE_SIZE * 2, ImageManager::GetInstance().GetImage(IMAGE_BACK_GROUND), true);
	}
	objectManager.Render(Object::RL_UNDER_TILE, cameraX);
	tileManager.Render(cameraX);
	objectManager.Render(Object::RL_GOAL, cameraX);
	objectManager.Render(Object::RL_ENEMY, cameraX);
	objectManager.Render(Object::RL_PLAYER, cameraX);
	objectManager.Render(Object::RL_ITEM, cameraX);
	objectManager.Render(Object::RL_CASTLE, cameraX);
	EffectManager::GetInstance().Render(cameraX);
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
			if (PlayerData::GetInstance().GetStock() > 1)
			{
				PlayerData::GetInstance().AddStock(-1);
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
					if (player->starTimer > 0)
					{
						enemy->Death(player->pos.x < enemy->pos.x);
					}
					else
					{

						// 踏んだかどうか
						if (player->CheckSquashEnemy(enemy))
						{
							if (enemy->GetEnemyType() == Enemy::ET_KOOPATROOPA)
							{
								KoopaTroopa* koopa = static_cast<KoopaTroopa*>(enemy);
								if (koopa->GetState() == KoopaTroopa::STATE_SHELL_STOP ||
									koopa->GetState() == KoopaTroopa::STATE_SHELL_WAKEUP)
								{
									koopa->OnKicked(player->pos.x);
								}
								else
								{
									enemy->OnSquashed();
								}
							}
							else
							{
								enemy->OnSquashed();
							}
						}
						else
						{
							if (enemy->GetEnemyType() == Enemy::ET_KOOPATROOPA)
							{
								KoopaTroopa* koopatroopa = static_cast<KoopaTroopa*>(enemy);

								if (koopatroopa->GetState() == KoopaTroopa::STATE_SHELL_STOP ||
									koopatroopa->GetState() == KoopaTroopa::STATE_SHELL_WAKEUP)
								{
									koopatroopa->OnKicked(player->pos.x);
								}
								else
								{
									if (enemy->canDamage) player->Damage();
								}
							}
							else
							{
								if (enemy->canDamage) player->Damage();
							}
						}
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
					item->isDead = true; // アイテムを消す
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
					case TileManager::ITEM_STAR:
						player->GetStar();
						break;

					}
				}
			}
		}
		if (obj->objectType == Object::OT_GOAL)
		{
			Goal* goal = static_cast<Goal*>(obj.get());
			if (goal && objectManager.HitObjects(player, goal))
			{
				float poleCenterX = goal->pos.x + (goal->size.w / 2.0f);
				player->OnGoal(poleCenterX);
			}
		}
		CheckHitFireballAndEnemy();
		CheckHitShellAndEnemy();
		CheckHitEnemyAndEnemy();
	}
}

void Stage::CheckHitFireballAndEnemy()
{
	for (const auto& fireObj : objectManager.GetObjects())
	{
		if (fireObj->objectType != Object::OT_FIREBALL)continue;
		Fireball* fireball = static_cast<Fireball*>(fireObj.get());

		for (const auto& enemyObj : objectManager.GetObjects())
		{
			if (enemyObj->objectType != Object::OT_ENEMY)continue;

			if (enemyObj->isDead)continue;

			if (objectManager.HitObjects(fireObj.get(), enemyObj.get()))
			{
				Enemy* enemy = static_cast<Enemy*>(enemyObj.get());

				enemy->Death(player->pos.x < enemy->pos.x);
				//enemyの死亡エフェクト
				fireball->DeathAndEffect();
				break;
			}
		}
	}
}

void Stage::CheckHitShellAndEnemy()
{
	for (const auto& shellObj : objectManager.GetObjects())
	{
		if (shellObj->objectType != Object::OT_SHELL)continue;

		if (objectManager.HitObjects(shellObj.get(), player))
		{
			Enemy* shellEnemy = static_cast<Enemy*>(shellObj.get());
			if (player->CheckSquashEnemy(shellEnemy))
			{
				if (shellEnemy->GetEnemyType() == Enemy::ET_KOOPATROOPA)
				{
					KoopaTroopa* koopa = static_cast<KoopaTroopa*>(shellEnemy);
					if (koopa->GetState() == KoopaTroopa::STATE_SHELL_STOP ||
						koopa->GetState() == KoopaTroopa::STATE_SHELL_WAKEUP)
					{
						koopa->OnKicked(player->pos.x);
					}
					else
					{
						shellEnemy->OnSquashed();
					}
				}
				else
				{
					shellEnemy->OnSquashed();
				}
			}
		}

		for (const auto& enemyObj : objectManager.GetObjects())
		{
			if (enemyObj->objectType != Object::OT_ENEMY)continue;
			if (enemyObj->isDead)continue;
			if (shellObj.get() == enemyObj.get())continue;
			if (objectManager.HitObjects(shellObj.get(), enemyObj.get()))
			{
				Enemy* enemy = static_cast<Enemy*>(enemyObj.get());

				enemy->Death(shellObj->speed.x > 0.0f);
				//enemyの死亡エフェクト
				break;
			}
		}
	}
}
void Stage::CheckHitEnemyAndEnemy()
{
	auto& objects = objectManager.GetObjects();

	// 敵同士の総当たり判定 (二重ループ)
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->objectType != Object::OT_ENEMY || objects[i]->isDead) continue;

		for (size_t j = i + 1; j < objects.size(); j++)
		{
			if (objects[j]->objectType != Object::OT_ENEMY || objects[j]->isDead) continue;

			// 同じオブジェクト同士でなければ判定
			if (objectManager.HitObjects(objects[i].get(), objects[j].get()))
			{
				Enemy* enemyA = static_cast<Enemy*>(objects[i].get());
				Enemy* enemyB = static_cast<Enemy*>(objects[j].get());

				if (enemyA->GetEnemyType() == Enemy::ET_KOOPATROOPA) {
					KoopaTroopa* kA = static_cast<KoopaTroopa*>(enemyA);
					if (kA->GetState() == KoopaTroopa::STATE_SHELL_ROLL) continue;
				}
				if (enemyB->GetEnemyType() == Enemy::ET_KOOPATROOPA) {
					KoopaTroopa* kB = static_cast<KoopaTroopa*>(enemyB);
					if (kB->GetState() == KoopaTroopa::STATE_SHELL_ROLL) continue;
				}

				// 反転
				enemyA->speed.x = -enemyA->speed.x;
				enemyB->speed.x = -enemyB->speed.x;

				// めり込み防止
				if (enemyA->pos.x < enemyB->pos.x)
				{
					enemyA->pos.x -= 1.0f;
					enemyB->pos.x += 1.0f;
				}
				else
				{
					enemyA->pos.x += 1.0f;
					enemyB->pos.x -= 1.0f;
				}
			}
		}
	}
}