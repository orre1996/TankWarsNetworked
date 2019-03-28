#pragma once
#include "IState.h"
#include "types.h"
#include "protocol.h"
#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include "Config.h"
#include "stdafx.h"

class StateReceiveChallenge : public IState
{
public:
	
	StateReceiveChallenge(Config::BufferWrapper p_bufferWrapper, ip_address p_localIp, uint64_t p_salt, udp_socket p_sock);
	~StateReceiveChallenge();
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
	uint64_t GetCombinedSalt();

	bool Timer(float p_delta);
	bool frequencyTimer(float p_delta);

	void SetSock(udp_socket& p_socket);
	//void SetServerIp(ip_address p_address);

	bool HasFoundConnection();
	uint64_t GetChallengeSalt();

	//uint8_t GetUniqueID();
	bool FinishedSearching();

private:
	bool hasReceived;
	uint64_t combinedSalt;
	uint64_t challengeSalt;
	float fTimer = 0;
	float fTimerMax = 10.0f;

	//float timeLineTimer = 0.0f;
	//float timeLineTimerCurrent = 100.0f;

	bool foundConnection;
	ip_address local_ip;
	udp_socket sock;
	float connectionTimer = 0;
	float lastSent = 0;
	float deltaConnectionTimer = 0;
	uint8_t uniqueID;

	Config::BufferWrapper bufferWrapper;
	uint8_t buffer[512];
	byte_stream stream_;
	uint64_t rdm_salt_;
};

