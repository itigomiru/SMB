#pragma once

#include "Object.h"
#include <vector>
#include <memory>
class ObjectManager
{
private:
	std::vector<std::unique_ptr<Object>> objects;
	std::vector<std::unique_ptr<Object>> newObjects;

public:
	void AddObject(std::unique_ptr<Object> object);
	void Update(float cameraX);
	void Render(float cameraX);
	bool HitObjects(Object* attacker, Object* target);
	const std::vector<std::unique_ptr<Object>>& GetObjects() const { return objects; }

	int GetFireballCount() const;
};