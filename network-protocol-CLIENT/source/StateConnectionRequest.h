#pragma once
#include "IState.h"
#include "types.h"
#include "protocol.h"
#include <stdarg.h>
#include <stdio.h>
#include <iostream>
#include "Config.h"

class StateConnectionRequest : public IState
{
public:
	StateConnectionRequest(Config::BufferWrapper p_bufferWrapper, ip_address p_ip, uint64_t p_salt, udp_socket p_sock);
	~StateConnectionRequest();

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

	bool Timer(float p_delta);
	bool frequencyTimer(float p_delta);
	
	void SetSock(udp_socket& p_socket);
	void SetServerIp(ip_address p_address);

	bool HasSent();

private:


	float fTimer = 0;
	float fTimerMax = 100.0f;
	
	bool isSent;
	ip_address server_ip;
	udp_socket sock;
	float connectionTimer = 0;
	float lastSent = 0;
	float deltaConnectionTimer = 0;

	Config::BufferWrapper bufferWrapper;
	uint8_t buffer[512];
	byte_stream stream_;
	uint64_t rdm_salt_;

};

