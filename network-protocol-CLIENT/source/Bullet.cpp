#include "stdafx.h"
#include "Tank.h"

#include "ServiceLocator.h"
#include "InputManager.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Sprite.h"
#include <math.h>
#include "Bullet.h"
#include <iostream>
#include "Vec.h"
#include "types.h"

#define PI = 3.14159265;

Bullet::Bullet(int p_x, int p_y, float angle)
{
	m_inputManager = ServiceLocator<InputManager>::GetService();
	m_Sprite = m_spriteManager->CreateSprite("Assets/preview.bmp", 175, 215, 12, 6);

	m_rotation = angle;
	vec2 position = { m_x, m_y };
	
	m_x = p_x;
	m_y = p_y;

	m_collider->m_rect.w = 6;
	m_collider->m_rect.h = 12;


	m_type = "Bullet";

	m_collider->m_rect.x = m_x;
	m_collider->m_rect.y = m_y;

	float ang = angle;
	//std::cout << "Angle: " << angle << '\n';
	if (ang != 0)
		forward = { cos( ang * (3.14f / 180.f) ), sin( ang * (3.14f / 180.f) ) };
	//std::cout << "x: "<< forward.x << '\n'<< "y: " << forward.y << '\n';
}

void Bullet::SetPosition(float p_x, float p_y)
{
	m_x = p_x;
	m_y = p_y;
}

void Bullet::SetRotation(float p_rotation)
{
	m_rotation = p_rotation;
}

void Bullet::SetEntityID(int p_id)
{
	id = p_id;
}

int Bullet::GetEntityID()
{
	return id;
}

Bullet::~Bullet()
{
}

void Bullet::Update(float p_delta)
{
	if (endPosition.x != m_x && endPosition.y != m_y && isLerping)
	{
		Interpolate(endPosition, p_delta);
	}
}

void Bullet::Draw()
{
	if (state == ALIVE)
		m_drawManager->NewDraw(m_Sprite, static_cast<int>(m_x), static_cast<int>(m_y), static_cast<int>(m_rotation), NULL, SDL_FLIP_NONE);
}

void Bullet::SetState(Entity_State p_value)
{
	state = p_value;
}

void Bullet::OnCollision(ICollideable * p_other)
{

}

// https://keithmaggio.wordpress.com/2011/02/15/math-magician-lerp-slerp-and-nlerp/
void Bullet::Interpolate(vec2 end, float p_delta)
{
	const float fDelta = static_cast<float>(p_delta) * 0.1f;

	const float percent = timer.UpdateTimer1(fDelta, 1.0f);

	isLerping = percent >= 1 ? 1 : 0;

	const vec2 newPosition = { startPosition.x + percent * (end.x - startPosition.x), startPosition.y + percent * (end.y - startPosition.y) };
	SetPosition(newPosition.x, newPosition.y);
}


void Bullet::SetEndPositionLerp(vec2 endPos)
{
	timer.resetTimer();
	startPosition = { m_x, m_y };
	endPosition = endPos;
	isLerping = true;
}

