#pragma once

#include <string>
#include "protocol.h"
#include "ICollideable.h"

class IEntity : public ICollideable
{
public:
	IEntity();
	~IEntity();
	virtual void Update(float p_delta) = 0;
	std::string GetType() const;
	int getEntityType() const;
	Entity_State getEntityState() const;
	void setEntityState(Entity_State p_state);
	int getEntityID() const;
	void setEntityID(int p_entityID);
	float getXPos() const;
	float getYPos() const;
	float GetRotation() const;
	void SetRotation(float p_rotation);
	void setPosition(float p_x, float p_y);
	virtual void setDeadCD();
protected:
	std::string m_type;

	float m_x;
	float m_y;
	int entityID = -1;
	float m_rotation;

	Entity_State currentState;
	int entityType;
};
