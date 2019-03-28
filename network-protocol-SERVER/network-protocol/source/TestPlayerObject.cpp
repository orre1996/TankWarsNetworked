#include "TestPlayerObject.h"
#include "Vec.h"

#define PI = 3.14159265;

TestPlayerObject::TestPlayerObject()
{
	m_collider->collisionRect.w = 1;
	m_collider->collisionRect.h = 1;
	m_x = 3.0f;
	m_y = 3.0f;

	m_type = "Player";
	entityID = 0;

	entityType = TANK;
	currentState = DEAD;


	shootCD = 1.0f;
	shootTimerCurrent = 0.0f;
	canShoot = true;

	movementDirection = { 0,0 };

}

TestPlayerObject::~TestPlayerObject()
{
}

vec2 TestPlayerObject::GetMovementDirection() const
{
	return movementDirection;
}

float TestPlayerObject::GetTankX() const
{
	return m_x;
}

float TestPlayerObject::GetTankY() const
{
	return m_y;
}

void TestPlayerObject::SendInput(uint8_t p_input, float p_delta)
{
	
	movementDirection = { 0,0 };

	Vec vec;
	const uint8_t firstBit = p_input & (1 << 0);
	const uint8_t SecondBit = p_input & (1 << 1);
	const uint8_t ThirdBit = p_input & (1 << 2);
	const uint8_t FourthBit = p_input & (1 << 3);

	if (firstBit > 0)
	{
		const vec2 upVec = { 0,-1 };
		movementDirection = { movementDirection.x + upVec.x, movementDirection.y + upVec.y };
	}

	if (SecondBit > 0)
	{
		const vec2 leftVec = { -1,0 };
		movementDirection = { movementDirection.x + leftVec.x, movementDirection.y + leftVec.y };

	}
	
	if (ThirdBit)
	{
		const vec2 downVec = { 0,1 };
		movementDirection = { movementDirection.x + downVec.x, movementDirection.y + downVec.y };

	}

	if (FourthBit > 0)
	{
		const vec2 rightVec = { 1,0 };
		movementDirection = { movementDirection.x + rightVec.x, movementDirection.y + rightVec.y };
	}


	movementDirection = vec.Normalize(movementDirection);

	if (currentState == ALIVE)
	{
		m_x += movementDirection.x * speed * p_delta;
		m_y += movementDirection.y * speed * p_delta;
		
	}

	m_collider->collisionRect.x = m_x;
	m_collider->collisionRect.y = m_y;

	
}

void TestPlayerObject::SetTankPos(float p_x, float p_y)
{
	m_x = p_x;
	m_y = p_y;

	m_collider->collisionRect.x = m_x;
	m_collider->collisionRect.y = m_y;
}

float TestPlayerObject::GetAngle()
{
	return 0.0f;
}

int TestPlayerObject::GetScore() const
{
	return score;
}

void TestPlayerObject::SetScore(int p_score)
{
	score = p_score;
}

void TestPlayerObject::IncreaseScore()
{
	score++;
}


void TestPlayerObject::setCurrentState(Entity_State p_currentState)
{
	currentState = p_currentState;
}

bool TestPlayerObject::getCanShoot() const
{
	return canShoot;
}

void TestPlayerObject::setCanShoot(bool p_value)
{
	canShoot = p_value;
}

void TestPlayerObject::setPositionSpawnPoint(int p_entityID)
{
	switch(entityID)
	{
	case 0:
		setPosition(4, 4);
			break;
	case 1:
		setPosition(50, 4);
		break;
	case 2:
		setPosition(4, 12);
		break;
	case 3:
		setPosition(50, 12);
		break;
	default: 
		break;
	}
}

float TestPlayerObject::getMiddleX() const
{
	return (m_collider->collisionRect.w / 2) + m_x;
}

float TestPlayerObject::getMiddleY() const
{
	return (m_collider->collisionRect.h / 2) + m_y;
}

void TestPlayerObject::setConnected(bool p_connected)
{
	connected = p_connected;
}

void TestPlayerObject::ShootingTimer(float p_deltaTime)
{
	
	if (shootTimerCurrent <= shootCD && !canShoot)
	{
		shootTimerCurrent += p_deltaTime;
	}
	else 
	{
		canShoot = true;
		shootTimerCurrent = 0.0f;
	}
}

void TestPlayerObject::setDeadCD()
{
	deadCD = network::get_ticks() + 3000;
}

bool TestPlayerObject::GetConnected() const
{
	return connected;
}

void TestPlayerObject::DeadTimer(float p_deltaTime)
{
	
	if(connected && network::get_ticks() >= deadCD)
	{
		setPositionSpawnPoint(entityID);
		setCurrentState(ALIVE);
	}
}

void TestPlayerObject::Update(float p_delta)
{
	ShootingTimer(p_delta);

	if(getEntityState() == DEAD)
	{
		DeadTimer(p_delta);
	}
}

void TestPlayerObject::OnCollision(ICollideable * p_other)
{

}

