
#include "TestPlayerObject.h"
#include "Bullet.h"
#include "Vec.h"

#define PI = 3.14159265;

Bullet::Bullet(const float p_x, const float p_y, const float p_angle)
{
	m_rotation = p_angle;
	vec2 position = {m_x, m_y};
	m_x = p_x;
	m_y = p_y;

	m_collider->collisionRect.w = 0.2f;
	m_collider->collisionRect.h = 0.4f;


	m_type = "Bullet";

	entityType = BULLET;
	currentState = DEAD;

	m_collider->collisionRect.x = m_x;
	m_collider->collisionRect.y = m_y;
}

Bullet::~Bullet() = default;

void Bullet::Update(float p_delta)
{

	forward = { 0,0 };
	if(m_rotation != 0)
	{
		forward = { cos(m_rotation*(3.14f / 180)), sin(m_rotation*(3.14f / 180)) };
	}

	if (currentState == ALIVE)
	{
		m_x += forward.x * (speed * p_delta); 
		m_y += forward.y * (speed * p_delta); 

		m_collider->collisionRect.x = m_x;
		m_collider->collisionRect.y = m_y;

	}
}


void Bullet::updateForward()
{
	forward = { 0,0 };
	if (m_rotation != 0)
	{
		forward = { cos(m_rotation*(3.14f / 180)), sin(m_rotation*(3.14f / 180)) };
	}

	if (currentState == ALIVE)
	{
		m_x += forward.x * speed;
		m_y += forward.y * speed;

		m_collider->collisionRect.x = m_x;
		m_collider->collisionRect.y = m_y;

	}
}

vec2 Bullet::getForward() const
{
	return forward;
}

float Bullet::GetBulletX() const
{
	return m_x;
}

float Bullet::GetBulletY() const
{
	return m_y;
}

void Bullet::OnCollision(ICollideable * p_other)
{

}

void Bullet::setCurrentState(Entity_State p_currentState)
{
	currentState = p_currentState;
}

TestPlayerObject* Bullet::GetCreator() const
{
	return creator;
}

void Bullet::setCreator(TestPlayerObject* p_creator)
{
	creator = p_creator;
}


