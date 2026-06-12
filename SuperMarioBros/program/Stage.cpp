#include "Main.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Float2.h"
#include "Fireball.h"
#include "ObjectManager.h"
#include "Player.h"
#include"ImageManager.h"
#include "EffectManager.h"
#include "ScoreEffect.h"
#include "Item.h"
#include "TileManager.h"
#include "EnemySpawner.h"
#include "PlayerData.h"
#include "Enemy.h"
#include "Object.h"
#include "KoopaTroopaController.h"
#include "Coin.h"
#include "Goal.h"
#include "FirebarController.h"
#include "LiftController.h"
#include "BowserController.h"
#include "Ui.h"
Stage::Stage(int num)
{
	tileManager.SetCurrentStage(num);
}
void Stage::Init()
{
	PlayerData::GetInstance().ResetTime();
	switch (tileManager.GetCurrentStage())
	{
	case 0:
		playerStartPos = { 32.0f, TILE_SIZE * 12 };
		break;
	case 1:
		playerStartPos = { 32.0f, TILE_SIZE * 6 };
		break;

	}
	UI::GetInstance().SetTileManager(&tileManager);
	auto p = std::make_unique<Player>(playerStartPos);
	player = p.get();
	player->SetStage(this);
	player->SetTileManager(&tileManager);
	player->SetObjectManager(&objectManager);
	player->SetState(PlayerData::GetInstance().GetPlayerState());
	objectManager.AddObject(std::move(p));
	enemySpawner.SetObjectManager(&objectManager);
	enemySpawner.SetTileManager(&tileManager);

	tileManager.SetTile();
	tileManager.SetObjectManager(&objectManager);
	enemySpawner.SetSpawner();
	

	objectManager.AddObject(std::make_unique<Goal>());

	objectManager.AddObject(std::make_unique<Coin>(30, 130));
}

void Stage::Update()
{
	EffectManager::GetInstance().Update();
	if (UpdateFreeze())return;
	if (tileManager.GetCurrentStage() != 2)CameraUpdate();
	PlayerData::GetInstance().AddTime(-1);
	if (PlayerData::GetInstance().GetTime() <= 0)
	{
		player->Death();
	}

	objectManager.Update(cameraX);
	enemySpawner.Update(cameraX);
	tileManager.Update();

	CheckHitPlayerAndLiftSide();
	CheckHit();
}

void Stage::Render()
{
	switch (tileManager.GetCurrentStage())
	{
	case 0:
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(132, 134, 225), true);
		for (int i = 0; i < 5; i++)
		{
			DrawGraph(i * 768 - static_cast<int>(cameraX), TILE_SIZE * 2, ImageManager::GetInstance().GetImage(IMAGE_BACK_GROUND), true);
		}
		break;
	case 1:
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), true);
		break;
	case 2:
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), true);
		break;
	}
	objectManager.Render(Object::RL_UNDER_TILE, cameraX);
	tileManager.Render(cameraX);
	objectManager.Render(Object::RL_GOAL, cameraX);
	objectManager.Render(Object::RL_ENEMY, cameraX);
	objectManager.Render(Object::RL_LIFT, cameraX);
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
				player->Init(playerStartPos);
				cameraX = 0.0f;
				SceneManager::GetInstance().ReserveScene(SceneManager::SCENE_PRESTAGE, tileManager.GetCurrentStage());
			}
			else SceneManager::GetInstance().ReserveScene(SceneManager::SCENE_GAMEOVER);
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
		if (obj->isDead)continue;
		if (obj->objectType == Object::OT_SHELL)
		{
			KoopaTroopa* shell = static_cast<KoopaTroopa*>(obj.get());
			if (!shell) continue;

			if (objectManager.HitObjects(player, shell))
			{
				if (player->starTimer > 0)
				{
					shell->Death(player->pos.x < shell->pos.x, 0);
				}
				else
				{
					auto state = shell->GetState();

					if (state == KoopaTroopa::STATE_SHELL_STOP || state == KoopaTroopa::STATE_SHELL_WAKEUP)
					{
						shell->OnKicked(player->pos.x);
					}
					else if (state == KoopaTroopa::STATE_SHELL_ROLL)
					{
						if (player->CheckSquashEnemy(shell))
						{
							shell->OnSquashed();
						}
						else if (shell->canDamage)
						{
							player->Damage();
						}
					}
				}
			}
		}

		if (obj->objectType == Object::OT_ENEMY)
		{
			Enemy* enemy = static_cast<Enemy*>(obj.get());
			if (!enemy) continue;

			// ファイアバーの特殊判定
			if (enemy->GetEnemyType() == Enemy::ET_FIREBAR)
			{
				Firebar* firebar = static_cast<Firebar*>(enemy);
				if (firebar->HitPlayer(player) && player->starTimer <= 0 && enemy->canDamage)
				{
					player->Damage();
				}
				continue;
			}

			// 通常の敵（歩いているノコノコやクリボーなど）との接触
			if (objectManager.HitObjects(player, enemy))
			{
				if (player->starTimer > 0)
				{
					enemy->Death(player->pos.x < enemy->pos.x, 0);
				}
				else
				{
					if (player->CheckSquashEnemy(enemy))
					{
						enemy->OnSquashed();
					}
					else if (enemy->canDamage)
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
					case TileManager::ITEM_COIN:
						PlayerData::GetInstance().AddCoin(1);
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
	}
	CheckHitFireballAndEnemy();
	CheckHitShellAndEnemy();
	CheckHitEnemyAndEnemy();
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

				if (enemy->GetEnemyType() == Enemy::ET_BOWSER)
				{
					Bowser* bowser = static_cast<Bowser*>(enemy);
					bowser->Damage();

					fireball->DeathAndEffect();
					break;
				}

				enemy->Death(player->pos.x < enemy->pos.x, 100);
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
		KoopaTroopa* shellEnemy = static_cast<KoopaTroopa*>(shellObj.get());
		if (shellEnemy->GetState() != KoopaTroopa::STATE_SHELL_ROLL)continue;

		for (const auto& enemyObj : objectManager.GetObjects())
		{
			if (enemyObj->objectType != Object::OT_ENEMY)continue;
			if (enemyObj->isDead)continue;
			if (shellObj.get() == enemyObj.get())continue;
			if (objectManager.HitObjects(shellObj.get(), enemyObj.get()))
			{
				Enemy* enemy = static_cast<Enemy*>(enemyObj.get());
				KoopaTroopa* shellEnemy = static_cast<KoopaTroopa*>(shellObj.get());

				enemy->Death(shellObj->speed.x > 0.0f, shellEnemy->comboCount);
				shellEnemy->comboCount++;
				if (shellEnemy->comboCount > ScoreEffect::SCORE_1UP) shellEnemy->comboCount = ScoreEffect::SCORE_1UP;
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
		if (objects[i]->isDead) continue;

		Enemy* enemyA = nullptr;


		if (objects[i]->objectType == Object::OT_ENEMY)
		{
			enemyA = static_cast<Enemy*>(objects[i].get());
		}
		else if (objects[i]->objectType == Object::OT_SHELL)
		{
			KoopaTroopa* koopaA = static_cast<KoopaTroopa*>(objects[i].get());
			if (koopaA->GetState() == KoopaTroopa::STATE_SHELL_ROLL) continue; 
			enemyA = koopaA;
		}

		if (!enemyA) continue; 

		for (size_t j = i + 1; j < objects.size(); j++)
		{
			if (objects[j]->isDead) continue;

			Enemy* enemyB = nullptr;

			if (objects[j]->objectType == Object::OT_ENEMY)
			{
				enemyB = static_cast<Enemy*>(objects[j].get());
			}
			else if (objects[j]->objectType == Object::OT_SHELL)
			{
				KoopaTroopa* koopaB = static_cast<KoopaTroopa*>(objects[j].get());
				if (koopaB->GetState() == KoopaTroopa::STATE_SHELL_ROLL) continue;
				enemyB = koopaB;
			}

			if (!enemyB) continue; // どちらでもなければスキップ

			// 衝突判定
			if (objectManager.HitObjects(enemyA, enemyB))
			{
				if (objects[i]->objectType == Object::OT_ENEMY)
				{
					enemyA->speed.x = -enemyA->speed.x;
				}
				if (objects[j]->objectType == Object::OT_ENEMY)
				{
					enemyB->speed.x = -enemyB->speed.x;
				}

				if (enemyA->pos.x < enemyB->pos.x)
				{
					if (objects[i]->objectType == Object::OT_ENEMY) enemyA->pos.x -= 1.0f;
					if (objects[j]->objectType == Object::OT_ENEMY) enemyB->pos.x += 1.0f;
				}
				else
				{
					if (objects[i]->objectType == Object::OT_ENEMY) enemyA->pos.x += 1.0f;
					if (objects[j]->objectType == Object::OT_ENEMY) enemyB->pos.x -= 1.0f;
				}
			}
		}
	}
}
void Stage::SetLift()
{
	if (tileManager.GetCurrentStage() == 0)
	{
		objectManager.AddObject(std::make_unique<Lift>(TILE_SIZE * 10.0f, TILE_SIZE * 8.0f, TILE_SIZE * 4.0f));
	}
}

void Stage::CheckHitPlayerAndLiftSide()
{
	for (const auto& obj : objectManager.GetObjects())
	{
		if (obj->objectType != Object::OT_LIFT) continue;
		if (obj->isDead) continue;

		Lift* lift = static_cast<Lift*>(obj.get());

		bool hit =
			player->pos.x + player->size.w > lift->pos.x &&
			player->pos.x < lift->pos.x + lift->size.w &&
			player->pos.y + player->size.h > lift->pos.y &&
			player->pos.y < lift->pos.y + lift->size.h;

		if (!hit) continue;

		// 上に乗ってる時は横壁判定しない
		if (player->pos.y + player->size.h <= lift->pos.y + 6.0f)
		{
			continue;
		}

		float playerCenterX = player->pos.x + player->size.w / 2.0f;
		float liftCenterX = lift->pos.x + lift->size.w / 2.0f;

		if (playerCenterX < liftCenterX)
		{
			player->pos.x = lift->pos.x - player->size.w;
		}
		else
		{
			player->pos.x = lift->pos.x + lift->size.w;
		}

		player->speed.x = 0.0f;
	}
}