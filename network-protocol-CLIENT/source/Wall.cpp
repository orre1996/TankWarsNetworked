#include "stdafx.h"
#include "Tank.h"

#include "ServiceLocator.h"
#include "InputManager.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Sprite.h"
#include <math.h>
#include "Wall.h"
#include <iostream>

#define PI = 3.14159265;

Wall::Wall(int p_x, int p_y)
{
	m_inputManager = ServiceLocator<InputManager>::GetService();
	m_Sprite = m_spriteManager->CreateSprite("Assets/treeSmall.bmp", 0, 0, 32, 32);

	m_x = p_x;
	m_y = p_y;

	m_collider->m_rect.w = 32;
	m_collider->m_rect.h = 32;


	m_type = "Wall";

	m_collider->m_rect.x = m_x;
	m_collider->m_rect.y = m_y;


}

Wall::~Wall()
{
}

void Wall::Update(float p_delta)

{

}

void Wall::Draw()
{
	m_drawManager->NewDraw(m_Sprite, static_cast<int>(m_x), static_cast<int>(m_y), static_cast<int>(m_rotation), NULL, SDL_FLIP_NONE);
}

void Wall::OnCollision(ICollideable * p_other)
{


}


