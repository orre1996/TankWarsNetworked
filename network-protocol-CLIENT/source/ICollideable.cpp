#include "stdafx.h"
#include "ICollideable.h"
#include "Collider.h"

ICollideable::ICollideable()
{
	m_collider = new Collider();
}

ICollideable::ICollideable(Collider* p_collider)
{
	m_collider = p_collider;
}

ICollideable::~ICollideable()
{
	delete m_collider;
	m_collider = nullptr;
}