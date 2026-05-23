#pragma once
#include "Scene.h"

class Clear : public Scene
{
	public:
	void Init() override;
	void Update() override;
	void Render() override;
	~Clear() override;
};