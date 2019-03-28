#pragma once
#include <cstdint>
#include <vector>
#include "protocol.h"

struct connection;
class LevelCreator;
class TestPlayerObject;
class CollisionManager;
class Wall;
class Bullet;
class IEntity;
class PlayState;
class ObjectPool;
class Game_Server

{
public:
	Game_Server();
	~Game_Server();
	void on_payload(uint8_t index, struct payload_packet* packet, connection& conn, uint8_t p_deltaTime);
	void Update(float p_delta, connection& conn);
	payload_packet GetPayload() const;

	void on_Connect(int connection_index);
	void on_Disonnect(int connection_index);
	void HandleInput(connection& p_conn, float p_delta);
	void CheckCollision(connection& p_conn);
	void ClearMessages();
	int getLatestDc() const;
	int getLatestConnect() const;
	float deltaTime = 0;
	float serverDelta = 0;


	TestPlayerObject* GetTank() const;

	std::vector<Bullet*> getBullets() const;
	std::vector<TestPlayerObject*> GetTanks() const;
	std::vector<IEntity*> GetEntities() const;
	std::vector<IEntity*> GetTanksAndBullets() const;
	
	int GetKillID() const;
	int GetVictimID() const;
	int GetKillMessageTries() const;

	void IncreaseKillMessageTries();
	Game_State GetCurrentGameState() const;
	void SetCurrentGameState(Game_State p_state);

	void setRoundTimer(int p_value);
	int getRoundTimer() const;




private:
	std::vector<InputMessage*> msgQueue;
	LevelCreator* levelCreator;
	TestPlayerObject* Tank;
	payload_packet payloadPacket;
	CollisionManager* collisionManager;
	std::vector<Wall*> walls;
	std::vector<TestPlayerObject*> Tanks;
	std::vector<IEntity*> entities;
	std::vector<IEntity*> tanksAndBullets;
	ObjectPool* objectPool;
	std::vector<Bullet*> bullets;
	int killerID = 0;
	int victimID = 0;
	int latestDC;
	int latestConnect;
	int killMessageTries = 100;
	int roundTime;
	Game_State currentGameState = WAITING;
};

