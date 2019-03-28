#pragma once
#include "IEntity.h"
#include "ICollideable.h"
#include "Vec.h"

class InputManager;
class ObjectPool;
struct MouseVector { float x = 0, y = 0; };

class TestPlayerObject : public IEntity
{
public:
	TestPlayerObject();
	virtual ~TestPlayerObject();
	void Update(float p_delta) override;
	void OnCollision(ICollideable* p_other) override;
	vec2 GetMovementDirection() const;
	float GetTankX() const;
	float GetTankY() const;
	void SendInput(uint8_t p_input, float p_delta);
	void SetTankPos(float p_x, float p_y);
	static float GetAngle();
	int GetScore() const;
	void SetScore(int p_score);
	void IncreaseScore();
	void setCurrentState(Entity_State p_currentState);
	bool getCanShoot() const;
	void setCanShoot(bool p_value);
	void setPositionSpawnPoint(int p_entityID);
	float getMiddleX() const;
	float getMiddleY() const;
	void setConnected(bool p_connected);
	void ShootingTimer(float p_deltaTime);
	void setDeadCD() override;
	bool GetConnected() const;
private:
	
	void DeadTimer(float p_deltaTime);
	float deadTimerCurrent;
	uint64_t deadCD = 0;
	float speed = 5;
	bool canShoot;
	float shootCD = 1.0f;
	float shootTimerCurrent;
	int score = 0;
	bool connected = false;

	vec2 movementDirection;


};