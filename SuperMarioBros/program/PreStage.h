#pragma once
#pragma once
#include "Scene.h"

class PreStage : public Scene
{
private:
    int nextStage;
	int timer = 0;
	const int DISPLAY_TIME = 90; 
public:
	PreStage(int stageNum = 0);
    void Init() override;
    void Update() override;
    void Render() override;
    ~PreStage() override;
};