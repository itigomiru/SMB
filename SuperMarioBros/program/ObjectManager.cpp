#include "ObjectManager.h"


void ObjectManager::AddObject(std::unique_ptr<Object> object)
{
	objects.push_back(object.release());
}

 void ObjectManager::Update() {
	for (auto obj = objects.begin(); obj != objects.end();) {
		(*obj)->Update();

		if ((*obj)->isDead) {
			obj = objects.erase(obj); // 死亡フラグが立っているオブジェクトをリストから削除
		}
		else {
			++obj;
		}
	}
}

  void ObjectManager::Render(float cameraX) {
	 for (auto& obj : objects) {
		 obj->Render(cameraX);
	 }
 }
