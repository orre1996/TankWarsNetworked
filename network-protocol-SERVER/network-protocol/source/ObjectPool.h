#pragma once
#include <vector>

class IEntity;
class ObjectPool
{
public:
	ObjectPool();
	~ObjectPool();

	IEntity* create(std::string p_type);
	void release(IEntity* p_entity);
	void AddToPool(IEntity* p_entity);

private:
	std::vector<IEntity*> entities;
};

