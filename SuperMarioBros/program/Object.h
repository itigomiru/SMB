#pragma once
#include "Float2.h"

class Object
{
public:
	Float2 pos;//位置
	Float2 speed;//速度
	Size size;//サイズ
	int objectType;//オブジェクトの種類

	virtual void Update() = 0;
	virtual void Render(float cameraX) = 0;

	bool isDead;//死亡フラグ

	enum ObjectType
	{
		PLAYER,
		PLAYER_BULLET, // 実体なし(攻撃判定しかないもの)
		ENEMY,
		ENEMY_BULLET, // 実体なし(攻撃判定しかないもの)
		ITEM,
	};
};