#include "stdafx.h"
#include "StateChallengeResponse.h"


StateChallengeResponse::StateChallengeResponse(Config::BufferWrapper p_bufferWrapper, ip_address p_ip, udp_socket p_sock, uint64_t& p_combinedSalt) :
	bufferWrapper(p_bufferWrapper),
	stream_(sizeof(bufferWrapper.buffer), bufferWrapper.buffer),
	server_ip(p_ip),
	sock(p_sock),
	combinedSalt(p_combinedSalt)
{
	isSent = false;
	numberOfSends = 0;
}


StateChallengeResponse::~StateChallengeResponse()
{

}


void StateChallengeResponse::Enter()
{
	std::cout << "Entering Challenge Response \n";

}

void StateChallengeResponse::Exit()
{
	isSent = false;
	numberOfSends = 0;
}

Config::BufferWrapper StateChallengeResponse::GetBuffer()
{
	return bufferWrapper;
}

void StateChallengeResponse::SetBuffer(Config::BufferWrapper p_buffer)
{
	bufferWrapper = p_buffer;
}

byte_stream StateChallengeResponse::GetByteStream()
{
	return stream_;
}

void StateChallengeResponse::SetByteStream(byte_stream p_stream)
{
	stream_ = p_stream;
}

uint64_t StateChallengeResponse::GetRandomSalt()
{
	return rdm_salt_;
}

void StateChallengeResponse::SetRandomSalt(uint64_t p_salt)
{
	rdm_salt_ = p_salt;
}

bool StateChallengeResponse::Timer(float p_delta)
{
	//one timer that goes to 5.
	//one timer that tells us if we should send.
	if (connectionTimer < 100000)
	{
		connectionTimer += p_delta;
		lastSent = connectionTimer;
		return false;
	}
	connectionTimer = 0.0f;
	return true;
}

bool StateChallengeResponse::frequencyTimer(float p_delta)
{
	if (fTimer < fTimerMax) {
		fTimer += p_delta;
		return false;
	}
	fTimer = 0.0f;
	return true;
}

void StateChallengeResponse::SetServerIp(ip_address p_address)
{
	server_ip = p_address;
}

bool StateChallengeResponse::HasSent()
{
	return isSent;
}

void StateChallengeResponse::Update(uint8_t p_delta)
{
	stream_.reset();
	challenge_response_packet challengeResponse;
	make_challenge_response_packet(challengeResponse, combinedSalt);
	byte_stream_writer writer(stream_);
	if (!Timer(p_delta))
	{
		if (frequencyTimer(p_delta))
		{
			if (serialize(challengeResponse, writer))
			{

				isSent = sock.send_to(server_ip, stream_);
				stream_.reset();
				std::cout << "Sending challenge Response" << '\n';
			}
			else
			{
				std::cout << "Could not Serialize in Challenge Response \n";
			}
		}
	}
	//change the state.
}

void StateChallengeResponse::Draw()
{
}