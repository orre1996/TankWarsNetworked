#pragma once
#include "IState.h" 
#include <vector>
#include <map>
#include "protocol.h"
class LevelCreator;
class TestPlayerObject;
class CollisionManager;
class Wall;
class Bullet;
class PlayState;
class Game_Server;

class PlayState : public IState
{
public:
	PlayState();
	~PlayState();
	void Update(float p_delta);
	void Enter();
	void Exit();
	TestPlayerObject* GetTank();

	std::vector<Bullet*> getBullets();

	std::vector<InputMessage*> msgQueue;
	LevelCreator* levelCreator;
	TestPlayerObject* Tank;
	payload_packet payloadPacket;
	CollisionManager* collisionManager;
	std::vector<Wall*> walls;

	std::vector<Bullet*> bullets;
};

