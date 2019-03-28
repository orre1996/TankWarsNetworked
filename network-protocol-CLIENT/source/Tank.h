#pragma once

#include "IEntity.h"
#include "IDrawable.h"
#include "ICollideable.h"
#include "Bullet.h"
#include <vector>
#include "Vec.h"
#include "Timer.h"

class InputManager;
struct MouseVector { float x = 0, y = 0; };

class Tank : public IEntity, public IDrawable, public ICollideable
{
public:
	Tank();
	virtual ~Tank();
	void Update(float p_delta);
	void Draw();
	void OnCollision(ICollideable* p_other);
	float Dot(MouseVector a, MouseVector b);
	float Length(MouseVector a);
	vec2 GetMovementDirection() const;
	float GetTankX() const;
	float GetTankY() const;
	void SetTankPos(float p_x, float p_y);
	float GetAngle() const;
	void SetRotation(float p_rotation);
	void SetState(Entity_State p_value);
	Entity_State GetState() const;
	int GetEntityID() const;
	void setRealTurretRotation(float p_value);
	void SetEntityID(int p_id);

	void Interpolate(vec2 end, float percent);
	void SetEndPositionLerp( vec2 endPos);
	void setPositionSpawnPoint(int entityID);

	void SendInput(uint8_t p_input, uint8_t p_delta);
	void CalculateNewInputPredictionElement( uint8_t p_newInput, vec2 oldPosition, vec2 newPosition, float deltaTime);
	void setMyID(int p_value);
	int GetMyID() const;


private:
	float m_TurretX;
	float m_TurretY;

	float m_PipeX;
	float m_PipeY;
	int entityID;

	bool isLerping = false;
	vec2 startPosition = { 0,0 };
	vec2 endPosition = { 0,0 };
	int myID = -1;

	void ShootingTimer(float p_deltaTime);
	float speed = 5.0f;
	bool canShoot;
	float shootCD;
	float shootTimerCurrent;
	float realTurretRotation = 0;
	SDL_Point PipeCenter;
	MouseVector PipeVecCenter;
	MouseVector mousePosition;
	MouseVector mouseVector;
	MouseVector rotationVector;

	MouseVector turretVector;
	vec2 movementDirection;

	float angle = 0;
	float m_rotation = 0;
	float m_PipeRotation = 0;
	float realRotation = 0;
	InputManager* m_inputManager;

	vector<Bullet*> bulletVector;
	Timer timer;

};