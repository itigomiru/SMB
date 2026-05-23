#pragma once
#include "DxLib.h"
#include "ImageManager.h"
#include "SceneManager.h"
#include "Random.h"



// =========================
// Effect Base
// =========================

class Effect {
protected:
	float x, y;
	bool isDead;

public:
	Effect(float x, float y)
		: x(x), y(y), isDead(false) {
	}

	Effect(float x, float y, int state)
		: x(x), y(y), isDead(false) {
	}

	virtual ~Effect() {}

	virtual void Update() = 0;
	virtual void Render() = 0;

	bool IsDead() const { return isDead; }
};


