#pragma once
#include "IEntity.h"
#include "IDrawable.h"
#include "ICollideable.h"
#include "stdafx.h"
#include "Vec.h"
#include "Timer.h"

class InputManager;

class Bullet : public IEntity, public IDrawable, public ICollideable
{
public:
	Bullet(int m_x, int m_y, float angle);
	virtual ~Bullet();
	void Update(float p_delta);
	void Draw();
	void OnCollision(ICollideable* p_other);
	void SetState(Entity_State p_value);
	void SetPosition(float p_x, float p_y);
	void SetRotation(float p_rotation);
	void SetEntityID(int p_id);
	int GetEntityID();

	void Interpolate(vec2 end, float p_delta);
	void SetEndPositionLerp(vec2 endPos);

private:


	bool isLerping = false;
	vec2 startPosition = { 0,0 }; 
	vec2 endPosition = { 0,0 };

	int id;
	float speed = 10;
	float m_rotation = 0;
	InputManager* m_inputManager;
	vec2 position;
	vec2 forward;
	Timer timer;
};