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

void Stage::Init()
{
    auto p = std::make_unique<Player>();
    player = p.get();
    player->SetTileManager(&tileManager);
    objectManager.AddObject(std::move(p));
	enemySpawner.SetObjectManager(&objectManager);

    tileManager.SetTile();
    enemySpawner.SetSpawner();
}

void Stage::Update()
{
    objectManager.Update();

    float targetX =
        player->pos.x - 128;

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
		player->vel.x = 0.0f;
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