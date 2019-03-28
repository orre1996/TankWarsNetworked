#include "stdafx.h"
#include "StateReceiveChallenge.h"
#include "util.h"



StateReceiveChallenge::StateReceiveChallenge(Config::BufferWrapper p_bufferWrapper, ip_address p_localIp, uint64_t p_salt, udp_socket p_sock)
	:
	bufferWrapper(p_bufferWrapper),
	stream_(sizeof(bufferWrapper.buffer), bufferWrapper.buffer),
	local_ip(p_localIp),
	rdm_salt_(p_salt),
	sock(p_sock)
{
	foundConnection = false;
	hasReceived = false;
}


StateReceiveChallenge::~StateReceiveChallenge()
{
}

void StateReceiveChallenge::Enter()
{
	hasReceived = false;
	fTimer = 0.0f;
	connectionTimer = 0.0f;
	std::cout << "Entering Receive Challenge State" << '\n';
}

void StateReceiveChallenge::Exit()
{
	//hasReceived = false;
	hasReceived = false;
	foundConnection = false;
}

Config::BufferWrapper StateReceiveChallenge::GetBuffer()
{
	return bufferWrapper;
}

void StateReceiveChallenge::SetBuffer(Config::BufferWrapper p_buffer)
{
	bufferWrapper = p_buffer;
}

byte_stream StateReceiveChallenge::GetByteStream()
{
	return stream_;
}

void StateReceiveChallenge::SetByteStream(byte_stream p_stream)
{
	stream_ = p_stream;
}

uint64_t StateReceiveChallenge::GetRandomSalt()
{
	return rdm_salt_;
}

void StateReceiveChallenge::SetRandomSalt(uint64_t p_salt)
{
	rdm_salt_ = p_salt;
}

uint64_t StateReceiveChallenge::GetCombinedSalt()
{
	return combinedSalt;
}

uint64_t StateReceiveChallenge::GetChallengeSalt()
{
	return challengeSalt;
}

bool StateReceiveChallenge::Timer(float p_delta)
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

bool StateReceiveChallenge::FinishedSearching()
{
	return hasReceived;
}

bool StateReceiveChallenge::frequencyTimer(float p_delta)
{
	if (fTimer < fTimerMax) {
		fTimer += p_delta;
		return false;
	}
	fTimer = 0.0f;
	return true;
}

bool StateReceiveChallenge::HasFoundConnection()
{
	return foundConnection;
}



void StateReceiveChallenge::Update(uint8_t p_delta)
{
	stream_.reset();
	byte_stream_reader reader(stream_);
	if (!Timer(p_delta))
	{
		if (frequencyTimer(p_delta))
		{
			foundConnection = sock.recv_from(local_ip, stream_);
			//std::cout << "ISSENT : " << hasReceived << '\n';
			connection_challenge_packet challenge;
			if (serialize(challenge, reader))
			{

				//printf("%llu", challenge.challenge_salt_);
				std::cout << "Successfully received challenge." << '\n';
				std::cout << "Connection found ? : " << foundConnection << '\n';
				hasReceived = true;
			}
			else
			{
				hasReceived = true;
				std::cout << "Failed to Receive \n";
			}
			challengeSalt = challenge.challenge_salt_;
			combinedSalt = challenge.client_salt_ ^ challenge.challenge_salt_;
			stream_.reset();

		}
	}

}




void StateReceiveChallenge::Draw()
{
}

/*
void StateReceiveChallenge::SetServerIp(ip_address p_ip)
{
	server_ip = p_ip;
}*/