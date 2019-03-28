#pragma once

#include <string>
#include "protocol.h"

class IEntity
{
public:
	IEntity();
	~IEntity();
	virtual void Update(float p_delta) = 0;
	const std::string GetType();

protected:
	std::string m_type;

	float m_x;
	float m_y;
	Entity_State state;


	/*
	float m_TankX;
	float m_TankY;
	*/


};
