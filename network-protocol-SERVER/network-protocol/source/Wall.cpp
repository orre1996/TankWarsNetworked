#include "stdafx.h"
#include "TestPlayerObject.h"

//#include "ServiceLocator.h"
//#include "InputManager.h"
//#include "SpriteManager.h"
//#include "DrawManager.h"
//#include "Sprite.h"
#include <math.h>
#include "Wall.h"
#include <iostream>

#define PI = 3.14159265;

Wall::Wall(float p_x, float p_y)
{


	m_x = p_x;
	m_y = p_y;
	m_rotation = 0;
	m_collider->collisionRect.w = 1;
	m_collider->collisionRect.h = 1;

	m_collider->collisionRect.x = m_x;
	m_collider->collisionRect.y = m_y;


	entityType = WALL;
	currentState = ALIVE;
	m_type = "Wall";
	entityID = 5;



}

Wall::~Wall() = default;

void Wall::Update(float p_delta)
{

}

void Wall::Draw()
{
}

void Wall::OnCollision(ICollideable * p_other)
{


}


