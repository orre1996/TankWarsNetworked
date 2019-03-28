#pragma once
#include "IEntity.h"
#include "ICollideable.h"
#include "Vec.h"

class InputManager;
class TestPlayerObject;

class Bullet : public IEntity
{
public:
	Bullet(float m_x, float m_y, float angle);
	virtual ~Bullet();
	void Update(float p_delta) override;
	void Draw();
	float GetBulletX() const;
	float GetBulletY() const;
	void OnCollision(ICollideable* p_other) override;
	void setCurrentState(Entity_State p_currentState);
	vec2 getForward() const;
	void updateForward();
	TestPlayerObject* GetCreator() const;
	void setCreator(TestPlayerObject* p_creator);
private:

	float speed = 10;
	vec2 forward;
	TestPlayerObject* creator;
	InputManager* m_inputManager;
	uint8_t uniqueID;
	vec2 position;
};