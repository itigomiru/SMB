#pragma once
#include "Scene.h"

class Gameover : public Scene
{
	public:
	void Init() override;
	void Update() override;
	void Render() override;
	~Gameover() override;
private:
	int timer = 0;
	const int GAMEOVER_DISPLAY_TIME = 240;
};