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

void Stage::Init()
{
	auto player = std::make_unique<Player>();
	objectManager.AddObject(std::move(player));
}

void Stage::Update()
{
	objectManager.Update();
}

void Stage::Render()
{
	objectManager.Render();
}

Stage::~Stage()
{

}