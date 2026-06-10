#pragma once
#pragma once
#include "Scene.h"

class PreStage : public Scene
{
public:
    void Init() override;
    void Update() override;
    void Render() override;
    ~PreStage() override;
};