#pragma once

#include "IEntity.h"
//#include "IDrawable.h"
#include "ICollideable.h"

class InputManager;

class Wall : public IEntity/*,*/ /*public IDrawable,*//* public ICollideable*/
{
public:
	Wall(float m_x, float m_y);
	virtual ~Wall();
	void Update(float p_delta);

	static void Draw();
	void OnCollision(ICollideable* p_other);
private:


	float m_rotation = 0;
	InputManager* m_inputManager;
};