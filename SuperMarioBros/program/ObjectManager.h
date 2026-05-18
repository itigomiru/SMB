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
	void Update() {
		for (auto obj = objects.begin(); obj != objects.end();) {
			(*obj)->update();
			
			if ((*obj)->isDead) {
				obj = objects.erase(obj); // 死亡フラグが立っているオブジェクトをリストから削除
			} else {
				++obj;
			}
		}
	}
	void Render() {
		for (auto& obj : objects) {
			obj->render();
		}
	}
};