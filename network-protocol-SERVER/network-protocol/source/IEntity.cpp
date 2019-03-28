#include "IEntity.h"

IEntity::IEntity() : m_type(""), m_x(0), m_y(0)
{

}

IEntity::~IEntity() = default;

std::string IEntity::GetType() const
{
	return m_type;
}

int IEntity::getEntityType() const
{
	return entityType;
}

Entity_State IEntity::getEntityState() const
{
	return currentState;
}

void IEntity::setEntityState(Entity_State p_state)
{
	currentState = p_state;
}

int IEntity::getEntityID() const
{
	return entityID;
}

void IEntity::setEntityID(int p_entityID)
{
	entityID = p_entityID;
}

float IEntity::getXPos() const
{
	return m_x;
}

float IEntity::getYPos() const
{
	return m_y;
}

float IEntity::GetRotation() const
{
	return m_rotation;
}

void IEntity::SetRotation(float p_rotation)
{
	m_rotation = p_rotation;
}

void IEntity::setPosition(const float p_x, const float p_y)
{
	m_x = p_x;
	m_y = p_y;
}

void IEntity::setDeadCD()
{
}
