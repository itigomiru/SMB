#pragma once
#include "Float2.h"

class Object
{
public:
	Float2 pos;//位置
	Float2 speed;//速度
	Size size;//サイズ
	int objectType;//オブジェクトの種類
	int renderLayer;

	virtual void Update(float cameraX) = 0;
	virtual void Render(float cameraX) = 0;

	bool isDead;//死亡フラグ

	enum ObjectType
	{
		OT_PLAYER,
		OT_PLAYER_BULLET, // 実体なし(攻撃判定しかないもの)
		OT_FIREBALL,
		OT_ENEMY,
		OT_ENEMY_BULLET, // 実体なし(攻撃判定しかないもの)
		OT_ITEM,
	};
	enum RenderLayer
	{
		RL_UNDER_TILE,
		RL_ENEMY,
		RL_PLAYER
	};
};