#include "ObjectManager.h"
#include "Hit.h"
#include <algorithm>

void ObjectManager::AddObject(std::unique_ptr<Object> object)
{
	newObjects.push_back(std::move(object));
}

 void ObjectManager::Update(float cameraX) {
	for (auto& obj : objects) {
		obj->Update(cameraX);
	}

	objects.insert(objects.end(), std::make_move_iterator(newObjects.begin()), std::make_move_iterator(newObjects.end()));
	newObjects.clear();

	objects.erase(
		std::remove_if(objects.begin(), objects.end(),
			[](const std::unique_ptr<Object>& obj) {
				return obj->isDead;
			}),
		objects.end());
}

  void ObjectManager::Render(float cameraX) {
	 for (auto& obj : objects) {
		 obj->Render(cameraX);
	 }
 }

  bool ObjectManager::HitObjects(Object* attacker, Object* target) {
	  return CheckBoxHit(attacker->pos, attacker->size, target->pos, target->size);
  }

  int ObjectManager::GetFireballCount() const {
	  int count = 0;
	  for (const auto& obj : objects) {
		  if (obj->objectType == Object::OT_FIREBALL) {
			  count++;
		  }
	  }
	  return count;
  }
