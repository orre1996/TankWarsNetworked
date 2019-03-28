#include "stdafx.h"
#include "StateConnectionRequest.h"
#include <iostream>

StateConnectionRequest::StateConnectionRequest(Config::BufferWrapper p_bufferWrapper, ip_address p_ip, uint64_t p_salt, udp_socket p_sock)
//Set buffer before this.
	:
	bufferWrapper(p_bufferWrapper),
	stream_(sizeof(bufferWrapper.buffer), bufferWrapper.buffer),
	server_ip(p_ip),
	rdm_salt_(p_salt),
	sock(p_sock)
{
	isSent = false;
}


StateConnectionRequest::~StateConnectionRequest()
{
}


void StateConnectionRequest::Enter()
{
	
	isSent = false;
	fTimer = 0.0f;
	connectionTimer = 0.0f;
	std::cout << "Entering Connection State Request \n";
}

void StateConnectionRequest::Exit()
{
	isSent = false;
}

Config::BufferWrapper StateConnectionRequest::GetBuffer()
{
	return bufferWrapper;
}

void StateConnectionRequest::SetBuffer(Config::BufferWrapper p_buffer)
{
	bufferWrapper = p_buffer;
}

byte_stream StateConnectionRequest::GetByteStream()
{
	return stream_;
}

void StateConnectionRequest::SetByteStream(byte_stream p_stream)
{
	stream_ = p_stream;
}

uint64_t StateConnectionRequest::GetRandomSalt()
{
	return rdm_salt_;
}

void StateConnectionRequest::SetRandomSalt(uint64_t p_salt)
{
	rdm_salt_ = p_salt;
}

bool StateConnectionRequest::Timer(float p_delta)
{
	//one timer that goes to 5.
	//one timer that tells us if we should send.
	if (connectionTimer < 10000)
	{
		connectionTimer += p_delta;
		lastSent = connectionTimer;
		return false;
	}
	connectionTimer = 0.0f;
	return true;
}

bool StateConnectionRequest::frequencyTimer(float p_delta)
{
	if (fTimer < fTimerMax) {
		fTimer += p_delta;
		return false;
	}
	fTimer = 0.0f;
	return true;
}

bool StateConnectionRequest::HasSent()
{
	return isSent;
}

void StateConnectionRequest::Update(uint8_t p_delta)
{

	connection_request_packet packet_;
	make_connection_request_packet(packet_, rdm_salt_);
	stream_.reset();
	byte_stream_writer writer(stream_);
	serialize(packet_, writer);

	if (!Timer(p_delta))
	{
		if (frequencyTimer(p_delta))
		{
			isSent = sock.send_to(server_ip, stream_);
			stream_.reset();
			//std::cout << hasReceived << '\n';
			//std::cout << udp_socket::get_error_code() << '\n';
			//std::cout << hasReceived << '\n';
			//winsock errorcodes.
		}
	}
	//change the state.
}

void StateConnectionRequest::Draw()
{
}

void StateConnectionRequest::SetServerIp(ip_address p_ip)
{
	server_ip = p_ip;
}