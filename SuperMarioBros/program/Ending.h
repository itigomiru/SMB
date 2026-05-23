#pragma once
#include "Scene.h"

class Ending : public Scene
{
	public:
	void Init() override;
	void Update() override;
	void Render() override;
	~Ending() override;
};