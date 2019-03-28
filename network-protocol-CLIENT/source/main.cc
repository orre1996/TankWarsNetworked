
#include "stdafx.h"
#include "types.h"
#include "protocol.h"


#include <cstdarg>
#include "stdio.h"
#include <iostream>
#include "StateMachine.h"
#include "StateConnectionRequest.h"
#include "StateReceiveChallenge.h"
#include "StateChallengeResponse.h"
#include "StateConnected.h"
#include "InputManager.h"
#include "ServiceLocator.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include <sstream>
#include "Lobby.h"
#include "GameRunner.h"
#include "Timer.h"

#if 0
uint32_t make_ip(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
	uint32_t result = 0;
	result |= (a & 0xFF) << 24;
	result |= (b & 0xFF) << 16;
	result |= (c & 0xFF) << 8;
	result = result | (d & 0xFF) << 0;
	return result;
}
#endif

#if 1
uint32_t make_ip(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
	uint32_t result = 0;
	result |= (a & 0xFF) << 24;
	result |= (b & 0xFF) << 16;
	result |= (c & 0xFF) << 8;
	result |= (d & 0xFF) << 0;
	return result;
}
#endif


static void
logf(const char *format, ...)
{
	char message[1024] = {};
	va_list args;
	va_start(args, format);
	vsprintf_s(message, sizeof(message), format, args);
	va_end(args);
	printf("%s\n", message);
}

enum client_state_type_id
{
	CLIENT_STATE_DISCONNECTED,
	CLIENT_STATE_SENDING_CONNECTION_REQUEST,
	CLIENT_STATE_SENDING_CHALLENGE_RESPONSE,
	CLIENT_STATE_CONNECTED,
	CLIENT_STATE_RECEIVING_CHALLENGE
};

struct client
{
	bool quit_{};
	client_state_type_id state_;
	udp_socket sock_;
	ip_address server_ip;
	uint64_t client_salt_{};
	uint64_t challenge_salt_{};
	int64_t connect_tick_{};
	int64_t last_send_tick{};
	int64_t last_recv_tick_{};
	uint32_t sequence_{};
};

InputManager* inputManager = new InputManager();


void HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event) == 1)
	{

		if (event.type == SDL_QUIT)
		{
		}
		else
		{
			inputManager->HandleEvent(event);
		}
	}
}

uint64_t time = 0;
uint64_t lastTick = 0;
uint8_t uniqueID;

bool timer(int64_t &p_current, int64_t p_max, uint8_t p_deltaTime)
{
	p_current = network::get_ticks();
	return p_current >= p_max;
}

bool DiscoveryResponse(udp_socket& p_sock, byte_stream& p_stream, ip_address& p_server_ip, uint8_t p_deltaTime)
{
	int64_t currentTime = 0;
	const int64_t waitTime = network::get_ticks() + 10;

	while (!timer(currentTime, waitTime, p_deltaTime))
	{
		if (p_sock.recv_from(p_server_ip, p_stream))
		{
			return true;
		}
	}
	return false;
}
bool ServerDiscovery(udp_socket& p_sock, uint64_t p_salt, ip_address& p_server_ip, uint8_t p_deltaTime)
{
	std::cout << "Entered server discovery \n";
	ip_address ips[1];
	ips[0].host_ = make_ip(192, 168, 43, 1);
	ips[0].port_ = PROTOCOL_DEFAULT_PORT;
	ip_address::local_addresses(1, ips);
	istringstream stream(ips[0].as_string());
	std::vector<std::string> outputVector;
	std::string outputIP;
	while (std::getline(stream, outputIP, '.'))
	{
		if (!outputIP.empty())
		{
			outputVector.push_back(outputIP);
		}
	}
	uint8_t buffer[512];
	for (int i = 0; i < 255; i++)
	{
		Timer timer;
		timer.WaitForSeconds(5);
		std::string::size_type sizeOne;
		std::string::size_type sizeTwo;
		std::string::size_type sizeThree;
		const int one = std::stoi(outputVector[0], &sizeOne);
		const int two = std::stoi(outputVector[1], &sizeTwo);
		const int three = std::stoi(outputVector[2], &sizeThree);

		byte_stream stream(sizeof(buffer), buffer);
		byte_stream_writer writer(stream);
		p_server_ip.host_ = make_ip(one, two, three, i);
		p_server_ip.port_ = PROTOCOL_DEFAULT_PORT;

		connection_request_packet connectionRequest{};
		make_connection_request_packet(connectionRequest, p_salt);
		if (!serialize(connectionRequest, writer))
			std::cout << "Could not serialize in server discovery \n";

		if (p_sock.send_to(p_server_ip, stream)) {
			stream.reset();
		}
		
	}

	for (int i = 0; i < 10; i++)
	{
		byte_stream responseStream(sizeof(buffer), buffer);
		std::cout << p_server_ip.as_string() << std::endl;
		if (DiscoveryResponse(p_sock, responseStream, p_server_ip, p_deltaTime))
		{
			std::cout << "returned true!" << '\n';
			std::cout << "Host ip: " << p_server_ip.as_string() << std::endl;
			responseStream.reset();
			return true;
		}
		responseStream.reset();
	}
	std::cout << "Returned false \n";
	return false;
}


int main(int argc, char **argv)
{
	auto foundIP = false;

	assert(SDL_Init(SDL_INIT_EVERYTHING) == 0 && "SDL_Init Failed");
	assert(TTF_Init() == 0 && "TTF_Init Failed");
	auto drawManager = new DrawManager();
	drawManager->Initialize();
	auto* spriteManager = new SpriteManager(drawManager->GetRenderer());
	inputManager->Initialize();
	ServiceLocator<InputManager>::SetService(inputManager);
	ServiceLocator<DrawManager>::SetService(drawManager);
	ServiceLocator<SpriteManager>::SetService(spriteManager);
	if (!network::init())
	{
		logf("error: could not initialize winsock!");
		return -1;
	}
	auto* stateManager = new StateMachine();

	client client_;
	client_.connect_tick_ = 1;
	client_.last_recv_tick_ = 0;
	client_.last_send_tick = 0;
	client_.state_ = CLIENT_STATE_SENDING_CONNECTION_REQUEST;


	udp_socket sock;
	ip_address server_ip;
	server_ip.host_ = make_ip(192, 168, 43, 1);
	server_ip.port_ = PROTOCOL_DEFAULT_PORT;

	ip_address ips[1];
	ips[0].host_ = make_ip(192, 168, 43, 1);
	ips[0].port_ = PROTOCOL_DEFAULT_PORT;

	ip_address::local_addresses(1, ips);
	istringstream stream(ips[0].as_string());

	std::vector<std::string> outputVector;
	std::string outputIP;


	while (std::getline(stream, outputIP, '.'))
	{
		if (!outputIP.empty())
		{
			outputVector.push_back(outputIP);
		}

	}
	ip_address local_ip;
	if (sock.open(local_ip))
	{
		//connection request
		const Config::BufferWrapper bufferWrapper;
		uint64_t rdm_salt = generate_random_salt();
		uint64_t challengeSalt;

		auto* stateConnectionRequest = new StateConnectionRequest(bufferWrapper, server_ip, rdm_salt, sock);
		stateManager->AddState("CLIENT_STATE_CONNECTION_REQUEST", stateConnectionRequest);
		const Config::BufferWrapper bufferWrapper2;
		local_ip.host_ = make_ip(192, 168, 1, 111);
		local_ip.port_ = PROTOCOL_DEFAULT_PORT;
		auto* stateReceiveChallenge = new StateReceiveChallenge(bufferWrapper2, local_ip, rdm_salt, sock);
		stateManager->AddState("CLIENT_STATE_RECEIVE_CHALLENGE", stateReceiveChallenge);

		auto* gameRunner = new GameRunner(true);
		ServiceLocator<GameRunner>::SetService(gameRunner);

		auto lobby = new Lobby();
		stateManager->AddState("LOBBY_STATE", lobby);
		stateManager->SetState("LOBBY_STATE");


		uint64_t combinedSalt;
		const Config::BufferWrapper bufferWrapper3;
		auto* stateChallengeResponse = new StateChallengeResponse(bufferWrapper3, server_ip, sock, combinedSalt);
		stateManager->AddState("CLIENT_STATE_CHALLENGE_RESPONSE", stateChallengeResponse);


		bool shouldQuit = false;
		auto* connectedState = new StateConnected(server_ip, local_ip, sock, combinedSalt, challengeSalt, shouldQuit);
		stateManager->AddState("CLIENT_STATE_CONNECTED", connectedState);

		bool isInGame = false;

		while (gameRunner->GetIsRunning())
		{
			time = network::get_ticks();
			const uint8_t deltaTime = (time - lastTick);
			lastTick = time;

			if (shouldQuit)
			{

				shouldQuit = false;
				isInGame = false;

				stateManager->SetState("LOBBY_STATE");
			}

			if (stateManager->GetCurrentState() == lobby)
			{
				if (lobby->GetIsInGame())
				{
					udp_socket discoverySock;
					ip_address garbageIp;
					discoverySock.open(garbageIp);
					rdm_salt = generate_random_salt();
					foundIP = ServerDiscovery(sock, rdm_salt, server_ip, deltaTime);
					discoverySock.close();

					if (foundIP)
					{
						std::cout << "I FOUND AN IP, I SHOULD HAVE DISCOVERED A SERVER \n";
						isInGame = true;
						stateConnectionRequest->SetRandomSalt(rdm_salt);
						stateManager->SetState("CLIENT_STATE_CONNECTION_REQUEST");
					}
					else
					{
						std::cout << "No ip was found, is the server running?" << '\n';
					}
				}
			}

			drawManager->SetDrawColor(0, 0, 0, 255);
			drawManager->Clear();
			stateManager->Update(deltaTime);
			inputManager->Update();
			stateManager->Draw();
			drawManager->Present();
			HandleEvents();


			if (isInGame)
			{
				if (stateManager->GetCurrentState() == stateConnectionRequest && stateConnectionRequest->HasSent())
				{
					stateReceiveChallenge->SetRandomSalt(rdm_salt);
					stateManager->SetState("CLIENT_STATE_RECEIVE_CHALLENGE");
				}
				if (stateManager->GetCurrentState() == stateReceiveChallenge && stateReceiveChallenge->HasFoundConnection())
				{
					stateReceiveChallenge->SetRandomSalt(rdm_salt);
					combinedSalt = stateReceiveChallenge->GetCombinedSalt();
					challengeSalt = stateReceiveChallenge->GetChallengeSalt();
					connectedState->SetServerIp(server_ip);
					stateChallengeResponse->SetServerIp(server_ip);
					stateManager->SetState("CLIENT_STATE_CHALLENGE_RESPONSE");
				}
				if (stateChallengeResponse->HasSent())
				{
					stateManager->SetState("CLIENT_STATE_CONNECTED");
					std::cout << "IP BEFORE CONNECTED" << server_ip.as_string();
					isInGame = false;
				}
			}
		}
	}


	network::shut();

	return 0;
}