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
				return obj->isDead && obj->objectType != Object::OT_PLAYER;
			}),
		objects.end());
}

 void ObjectManager::Render(int layer,float cameraX)
 {
	 for (auto& obj : objects)
	 {
		 if (obj->renderLayer == layer && obj->isDead == false)
		 {
			 obj->Render(cameraX);
		 }
		 if (obj->objectType == Object::OT_PLAYER && obj->isDead)
		 {
			 obj->Render(cameraX);
		 }
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

  void ObjectManager::AllClear() {
	  objects.erase(
		  std::remove_if(objects.begin(), objects.end(),
			  [](const std::unique_ptr<Object>& obj) {
				  return obj->objectType != Object::OT_PLAYER;
			  }),
		  objects.end());
	  newObjects.clear();
  }
