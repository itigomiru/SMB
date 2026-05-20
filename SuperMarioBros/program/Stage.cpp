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

void Stage::Init()
{
    auto p = std::make_unique<Player>();
    player = p.get();
    player->SetTileManager(&tileManager);
    objectManager.AddObject(std::move(p));

    tileManager.SetTile();
}

void Stage::Update()
{
    objectManager.Update();

    if (player->pos.x > 128)
    {
        cameraX =
            player->pos.x - 128;
    }

    if (cameraX < 0)
    {
        cameraX = 0;
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