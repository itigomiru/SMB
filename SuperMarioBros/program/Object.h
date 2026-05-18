#pragma once
#include "Float2.h"

class Object
{
public:
	Float2 pos;//位置
	Float2 vel;//加速度
	Size size;//サイズ

	virtual void update() = 0;
	virtual void render() = 0;

	bool isDead;//死亡フラグ
};