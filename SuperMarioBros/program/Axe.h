#pragma once
#include "Object.h"
class Axe : public Object
{
public:
    Axe();

    void Update(float cameraX) override;
    void Render(float cameraX) override;
};