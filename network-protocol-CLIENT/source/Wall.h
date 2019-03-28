#pragma once

#include "IEntity.h"
#include "IDrawable.h"
#include "ICollideable.h"

class InputManager;

class Wall : public IEntity, public IDrawable, public ICollideable
{
public:
	Wall(int m_x, int m_y);
	virtual ~Wall();
	void Update(float p_delta);
	void Draw();
	void OnCollision(ICollideable* p_other);
private:
	float m_rotation = 0;
	InputManager* m_inputManager;
};