#include "stdafx.h"
#include "IEntity.h"

IEntity::IEntity() : m_type(""), m_x(0), m_y(0)
{

}

IEntity::~IEntity()
{
}

const std::string IEntity::GetType()
{
	return m_type;
}
