#pragma once

#include "Object.h"
#include <vector>
#include <memory>
class ObjectManager
{
private:
	std::vector<Object*> objects;

public:
	void AddObject(std::unique_ptr<Object> object);
	void Update();
	void Render(float cameraX);


};