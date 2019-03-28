#pragma once
#include "Vec.h"

class Collider;
class ICollideable;

class CollisionManager
{
public:
	static bool CheckCollision(Collider* p_first, Collider* p_second);
	static bool CheckCollision(ICollideable* p_first, ICollideable* p_second);
	static vec2 GetNormalOfRect(Collider* p_first, Collider* p_second);
	static vec2 CalculateCollisionOverlap(Collider* p_first, Collider* p_second);
};

