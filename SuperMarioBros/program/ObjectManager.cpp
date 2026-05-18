#include "ObjectManager.h"


void ObjectManager::AddObject(std::unique_ptr<Object> object)
{
	objects.push_back(object.release());
}