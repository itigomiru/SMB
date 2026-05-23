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
	int state;

public:
	Effect(float x, float y)
		: x(x), y(y), isDead(false), state(0) {
	}

	Effect(float x, float y, int state)
		: x(x), y(y), isDead(false), state(state) {
	}

	virtual ~Effect() {}

	virtual void Update() = 0;
	virtual void Render() = 0;

	bool IsDead() const { return isDead; }
};

