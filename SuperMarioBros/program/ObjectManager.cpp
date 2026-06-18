#include "ObjectManager.h"
#include "Hit.h"
#include "Enemy.h"
#include <algorithm>

void ObjectManager::AddObject(std::unique_ptr<Object> object)
{
	newObjects.push_back(std::move(object));
}

void ObjectManager::Update(float cameraX) {
	if (!newObjects.empty()) {
		objects.insert(objects.end(), std::make_move_iterator(newObjects.begin()), std::make_move_iterator(newObjects.end()));
		newObjects.clear();
	}

	for (auto& obj : objects) {
		obj->Update(cameraX);
	}

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
	  return CheckBoxHit(attacker->hitBoxPos, attacker->hitBoxSize, target->hitBoxPos, target->hitBoxSize);
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

  void ObjectManager::RemoveEnemyBullet() {
	  for (auto& obj : objects) {
		  if (obj->objectType == Object::OT_ENEMY_BULLET) {
			  obj->isDead = true;
		  }
	  }
  }
  bool ObjectManager::SearchBowser() const {
	  for (const auto& obj : objects) {
		  if (obj->objectType == Object::OT_ENEMY) {
			  Enemy* enemy = static_cast<Enemy*>(obj.get());
			  if(enemy->GetEnemyType() == Enemy::ET_BOWSER)return true;
		  }
	  }
	  return false;
  }