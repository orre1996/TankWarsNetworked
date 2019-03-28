#pragma once
#include "IState.h"
#include "types.h"
#include "protocol.h"
#include <stdarg.h>
#include <stdio.h>
#include "stdafx.h"
#include <iostream>
#include "Config.h"
#include "LevelCreator.h"

struct vec2;
class InputManager;
class Tank;
class Wall;
class Bullet;
class HUD;
class GameplayMessages;
class SubMenu;

class StateConnected : public IState
{
public:

	struct inputPredictionStruct
	{
		uint8_t input;
		uint16_t uniqueID;
		float PosX;
		float PosY;
		uint8_t deltaTime;

	};

	std::vector<inputPredictionStruct*> inputPredictionStructs;
	std::vector<message*> msgQueue;

	StateConnected(ip_address& p_hostIp, ip_address& p_localIp, udp_socket& p_sock, uint64_t& p_combinedSalt, uint64_t& p_challengeSalt, bool &p_shouldQuit);
	~StateConnected();
	void Enter();
	void Update(uint8_t p_delta);
	void Draw();
	void Exit();

	Config::BufferWrapper GetBuffer();
	void SetBuffer(Config::BufferWrapper p_buffer);
	byte_stream GetByteStream();
	void SetByteStream(byte_stream p_stream);
	uint64_t GetRandomSalt();
	void SetRandomSalt(uint64_t p_salt);

	bool Timer1(float p_delta);
	bool frequencyTimerOne(uint8_t p_delta);
	bool frequencyTimerTwo(uint8_t p_delta);

	void SetServerIp(ip_address p_address);
	void SetChallengeSalt(uint64_t p_salt);

	void SendAndReceive(uint8_t p_delta);
	void CollisionCheck();


	bool HasSent();
	bool CheckInputPredictionAccuracy(float myX, float myY, float serverX, float serverY) const;
	void RecalculateCurrentPosition(local_entity_state message, int p_currentPos);
	void DeleteOldPredictions(uint16_t uniqueID);
	void CreateNewInputPredictionElement(inputPredictionStruct& a, inputPredictionStruct& b, uint8_t deltaTime);

	void setDeltaTime(uint8_t p_value);

private:

	uint8_t clientCanSend = 33;
	uint8_t clientCanReceive = 33;
	uint8_t clientSendRate = 33;
	int latestReceivedSequence = 0;
	uint32_t sequence = 0;
	GameplayMessages* gameplayMessages;
	HUD* hud;
	uint16_t uniqueID = 0;
	uint16_t lastUniqueID = 0;
	std::vector<Bullet*> bullets;
	std::vector<Wall*> walls;
	std::vector<Tank*> tanks;

	int myID = 255;
	uint64_t lastRoundTripTime = 0;

	LevelCreator* levelCreator;
	Tank* playerTank;
	InputManager* inputManager = nullptr;
	uint64_t& combinedSalt;
	uint64_t& challengeSalt;
	float fTimerOne = 0;
	float fTimerOneMax = 0.033f;
	float fTimerTwo = 0;
	float fTimerTwoMax = 0.033f;
	float fDelta = 0;
	uint8_t deltaTime = 0;

	bool hasReceived;
	bool hasSent;
	bool& shouldQuit;
	bool hasDisconnected;
	ip_address local_ip;
	ip_address server_ip;
	udp_socket sock;
	float connectionTimer = 0;
	float lastSent = 0;
	float deltaConnectionTimer = 0;


	Config::BufferWrapper bufferWrapper;
	uint8_t buffer[512];
	byte_stream stream_;
	uint64_t rdm_salt_;

	SubMenu* subMenu;

	float scale;
	float speed;
};