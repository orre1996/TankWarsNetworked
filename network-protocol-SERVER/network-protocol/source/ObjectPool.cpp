#include "ObjectPool.h"
#include "IEntity.h"
#include <cassert>
#include <string>
#include "ServiceLocator.h"


ObjectPool::ObjectPool()
{
	
}


ObjectPool::~ObjectPool()
{
	for (int i = 0; i < entities.size(); i++)
	{
		delete entities[i];
		entities[i] = nullptr;
	}
	entities.clear();
}

IEntity* ObjectPool::create(std::string p_type)
{
	for (int i = 0; i < entities.size(); i++)
	{
		if(entities[i]->getEntityState() == DEAD && entities[i]->GetType() == p_type)
		{
			entities[i]->setEntityState(ALIVE);
			return entities[i];
		}
	}
	assert(1 == 1 && "objet was nullptr");
	return nullptr;
}

void ObjectPool::release(IEntity* p_entity)
{
	p_entity->setEntityState(DEAD);
}

void ObjectPool::AddToPool(IEntity* p_entity)
{
	entities.push_back(p_entity);
}


