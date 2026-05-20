#pragma once
#include "Float2.h"

class Object
{
public:
	Float2 pos;//位置
	Float2 vel;//加速度
	Size size;//サイズ

	virtual void Update() = 0;
	virtual void Render(float cameraX) = 0;

	bool isDead;//死亡フラグ
};