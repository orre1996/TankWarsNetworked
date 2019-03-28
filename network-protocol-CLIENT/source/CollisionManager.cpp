#include "stdafx.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "ICollideable.h"
#include <iostream>
#include <math.h>
#include <algorithm>


bool CollisionManager::CheckCollision(Collider* p_first, Collider* p_second)
{
	float first_left = p_first->m_rect.x;
	float first_right = p_first->m_rect.x + p_first->m_rect.w;
	float first_up = p_first->m_rect.y;
	float first_down = p_first->m_rect.y + p_first->m_rect.h;

	float second_left = p_second->m_rect.x;
	float second_right = p_second->m_rect.x + p_second->m_rect.w;
	float second_up = p_second->m_rect.y;
	float second_down = p_second->m_rect.y + p_second->m_rect.h;

	if (first_right  <  second_left ||
		second_right <  first_left ||
		first_down   <  second_up ||
		second_down  <  first_up)
	{
		return false;
	}
	return true;
};

bool CollisionManager::CheckCollision(ICollideable* p_first, ICollideable* p_second)
{

	if (CollisionManager::CheckCollision(p_first->m_collider, p_second->m_collider))
	{
		p_first->OnCollision(p_second);
		p_second->OnCollision(p_first);
		return true;
	}
	return false;
};

vec2 CollisionManager::CalculateCollisionOverlap(Collider* p_first, Collider* p_second)
{
	float first_left = p_first->m_rect.x;
	float first_right = p_first->m_rect.x + p_first->m_rect.w;
	float first_up = p_first->m_rect.y;
	float first_down = p_first->m_rect.y + p_first->m_rect.h;

	float second_left = p_second->m_rect.x;
	float second_right = p_second->m_rect.x + p_second->m_rect.w;
	float second_up = p_second->m_rect.y;
	float second_down = p_second->m_rect.y + p_second->m_rect.h;

	float x_overlap = std::max(0.0f, std::min(first_right, second_right) - std::max(first_left, second_left));
	float y_overlap = std::max(0.0f, std::min(first_down, second_down) - std::max(first_up, second_up));

	vec2 overLapVec = { abs(x_overlap),abs(y_overlap) };
	return overLapVec;
}

vec2 CollisionManager::GetNormalOfRect(Collider* p_first, Collider* p_second)
{
	float first_left = p_first->m_rect.x;
	float first_right = p_first->m_rect.x + p_first->m_rect.w;
	float first_up = p_first->m_rect.y;
	float first_down = p_first->m_rect.y + p_first->m_rect.h;

	float second_left = p_second->m_rect.x;
	float second_right = p_second->m_rect.x + p_second->m_rect.w;
	float second_up = p_second->m_rect.y;
	float second_down = p_second->m_rect.y + p_second->m_rect.h;

	float first_midPointX = p_first->m_rect.x + p_first->m_rect.w / 2;
	float first_midPointY = p_first->m_rect.y + p_first->m_rect.h / 2;

	float second_midPointX = p_second->m_rect.x + p_second->m_rect.w / 2;
	float second_midPointY = p_second->m_rect.y + p_second->m_rect.h / 2;

	float dx = first_midPointX < second_midPointX ? -1 : 1;
	float dy = first_midPointY < second_midPointY ? -1 : 1;

	//https://gamedev.stackexchange.com/questions/48816/how-to-calculate-collision-normal-between-two-axisalignedboxs
	//Calculating Normal of our boxes ^
	int xOverlap = std::max(0.0f, std::min(first_right, second_right) - std::max(first_left, second_left));
	int yOverlap = std::max(0.0f, std::min(first_down, second_down) - std::max(first_up, second_up));

	//find the edge of object we are colliding with.
	vec2 normalVec = { 0,0 };
	if (xOverlap <= yOverlap)
		normalVec = { (float)dx,0 };
	else/* if (xOverlap > yOverlap)*/
		normalVec = { 0,(float)dy };
	/*else
	{
	//this shouldn't be the case i think.
	normalVec = { 0,0 }; //if they are equal, do nothing, otherwise sliding can stop.
	}*/

	return normalVec;
};
