#include "stdafx.h"
#include "Tank.h"

#include "ServiceLocator.h"
#include "InputManager.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "Vec.h"
#include "types.h"
#include <algorithm>
#include "Timer.h"
#include <iostream>

#define PI = 3.14159265;

Tank::Tank()
{
	m_inputManager = ServiceLocator<InputManager>::GetService();
	m_TankSprite = m_spriteManager->CreateSprite("Assets/preview.bmp", 177, 110, 35, 35);
	m_TurretSprite = m_spriteManager->CreateSprite("Assets/preview.bmp", 274, 71, 20, 20);
	m_TurretPipeSprite = m_spriteManager->CreateSprite("Assets/preview.bmp", 181, 329, 27, 11);
	m_Sprite = m_spriteManager->CreateSprite("Assets/dirt.png", 0, 0, 124, 124);
	state = DEAD;

	m_collider->m_rect.w = 32;
	m_collider->m_rect.h = 32;
	m_x = 100;
	m_y = 100;

	m_TurretX = 100 + 7;
	m_TurretY = 100 + 7;

	m_PipeX = 100 + 15;
	m_PipeY = 100 - 4;
	m_type = "Player";

	turretVector = { 0,1 };
	PipeCenter = { (m_TurretPipeSprite->GetSource().w), m_TurretPipeSprite->GetSource().h / 2 };
	shootCD = 1.0f;
	shootTimerCurrent = 0.0f;
	canShoot = true;
	movementDirection = { 0,0 };
}

Tank::~Tank()
{
}

void Tank::SetEntityID(int p_id)
{
	entityID = p_id;
}

int Tank::GetEntityID() const
{
	return entityID;
}

void Tank::setRealTurretRotation(float p_value)
{
	realTurretRotation = p_value;
}

vec2 Tank::GetMovementDirection() const
{
	return movementDirection;
}

float Tank::GetTankX() const
{
	return m_x;
}

float Tank::GetTankY() const
{
	return m_y;
}

void Tank::SetTankPos(float p_x, float p_y)
{
	m_x = p_x;
	m_y = p_y;
	m_collider->m_rect.x = static_cast<int>(m_x);
	m_collider->m_rect.y = static_cast<int>(m_y);
}

void Tank::ShootingTimer(float p_deltaTime)
{
	if (shootTimerCurrent < 1 && !canShoot)
	{
		shootTimerCurrent += p_deltaTime;
	}
	else {
		canShoot = true;
		shootTimerCurrent = 0.0f;
	}
}

void Tank::Update(float p_delta)
{
	mousePosition.x = static_cast<float>(m_inputManager->GetMousePosition().x);
	mousePosition.y = static_cast<float>(m_inputManager->GetMousePosition().y);

	mouseVector.x = mousePosition.x - m_x - m_TankSprite->GetSource().w / 2;
	mouseVector.y = mousePosition.y - m_y - m_TankSprite->GetSource().h / 2;

	angle = atan2(mouseVector.y, mouseVector.x);
	angle = angle * (180.0f / 3.14159265f);

	m_PipeRotation = angle;

	if (endPosition.x != m_x && endPosition.y != m_y && myID != entityID && isLerping)
	{
		Interpolate(endPosition, p_delta);
	}
	
}

void Tank::Draw()
{
	if (state == ALIVE)
	{
		m_TurretX = m_x + 7.0f;
		m_TurretY = m_y + 7.0f;

		m_PipeX = m_x - 9.0f;
		m_PipeY = m_y + 12.0f;

		m_drawManager->NewDraw(m_TankSprite, static_cast<int>(m_x) , static_cast<int>(m_y), m_rotation, NULL, SDL_FLIP_NONE);
		m_drawManager->NewDraw(m_TurretSprite, static_cast<int>(m_TurretX), static_cast<int>(m_TurretY), m_rotation, NULL, SDL_FLIP_NONE);
		m_drawManager->NewDraw(m_TurretPipeSprite, static_cast<int>(m_PipeX), static_cast<int>(m_PipeY), realTurretRotation + 180, &PipeCenter, SDL_FLIP_NONE);
	}
}

void Tank::OnCollision(ICollideable * p_other)
{

}

void Tank::SetRotation(float p_rotation)
{
	angle = p_rotation;
}

float Tank::GetAngle() const
{
	return angle;
}


void Tank::SetState(Entity_State p_value)
{
	state = p_value;
}

Entity_State Tank::GetState() const
{
	return state;
}

// https://keithmaggio.wordpress.com/2011/02/15/math-magician-lerp-slerp-and-nlerp/
void Tank::Interpolate( vec2 end, float delta)
{
	const float fDelta = static_cast<float>(delta) * 0.02f;

	const float percent = timer.UpdateTimer1(fDelta, 1.0f);

	isLerping = percent >= 1 ? 1 : 0;

	const vec2 newPosition = { startPosition.x + percent * (end.x - startPosition.x), startPosition.y + percent * (end.y - startPosition.y) };
	SetTankPos(newPosition.x, newPosition.y);
}


void Tank::SetEndPositionLerp( vec2 endPos)
{
	timer.resetTimer();
	startPosition = { m_x, m_y };
	endPosition = endPos;
	isLerping = true;
}

void Tank::SendInput(uint8_t p_input, uint8_t p_delta)
{
	
	movementDirection = { 0,0 };
	
	Vec vec;
	uint8_t firstBit = p_input & (1 << 0);
	uint8_t SecondBit = p_input & (1 << 1);
	uint8_t ThirdBit = p_input & (1 << 2);
	uint8_t FourthBit = p_input & (1 << 3);

	m_rotation = 0;

	if (firstBit > 0)
	{
		vec2 upVec = { 0,-1 };
		movementDirection = { movementDirection.x + upVec.x, movementDirection.y + upVec.y };
	
	}

	if (SecondBit > 0)
	{
		vec2 leftVec = { -1,0 };
		movementDirection = { movementDirection.x + leftVec.x, movementDirection.y + leftVec.y };

	}

	if (ThirdBit)
	{
		vec2 downVec = { 0,1 };
		movementDirection = { movementDirection.x + downVec.x, movementDirection.y + downVec.y };
	}

	if (FourthBit > 0)
	{
		vec2 rightVec = { 1,0 };
		movementDirection = { movementDirection.x + rightVec.x, movementDirection.y + rightVec.y };
	}

	movementDirection = vec.Normalize(movementDirection);

	const float fDelta = static_cast<float>(p_delta) * 0.001f;

	if (state == ALIVE)
	{
		m_x += movementDirection.x * speed * 32.0f * fDelta;
		m_y += movementDirection.y * speed * 32.0f * fDelta;
	}

	m_collider->m_rect.x = static_cast<int>(m_x);
	m_collider->m_rect.y = static_cast<int>(m_y);
}

void Tank::setPositionSpawnPoint(int entityID)
{
	switch (entityID)
	{
	case 0:
		SetTankPos(128.0f, 128.0f);
		break;
	case 1:
		SetTankPos(1600.0f, 128.0f);
		break;
	case 2:
		SetTankPos(128.0f, 384.0f);
		break;
	case 3:
		SetTankPos(384.0f, 1600.0f);
		
	default:;
	}
}

void Tank::setMyID(int p_value)
{
	myID = p_value;
}

int Tank::GetMyID() const
{
	return myID;
}
