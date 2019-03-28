#include "stdafx.h"
#include "HUD.h"
#include "TextString.h"


HUD::HUD()
{
	textManager = new TextString();
	textManager1 = new TextString();
	playerScores.push_back(-1);
	playerScores.push_back(-1);
	playerScores.push_back(-1);
	playerScores.push_back(-1);

	playerID.push_back(-1);
	playerID.push_back(-1);
	playerID.push_back(-1);
	playerID.push_back(-1);

	playerPing.push_back(-1);
	playerPing.push_back(-1);
	playerPing.push_back(-1);
	playerPing.push_back(-1);


	time = 0;
	//m_states.insert(std::pair<std::string, IState*>(p_name, p_state));
	gameStateMap.insert(std::pair<int, std::string>(0, "RUNNING"));
	gameStateMap.insert(std::pair<int, std::string>(1, "WAITING"));
	gameStateMap.insert(std::pair<int, std::string>(2, "PAUSED"));

}


HUD::~HUD()
{
}

void HUD::SetState(int p_state)
{
	currentGameState = gameStateMap.at(p_state);
}

void HUD::Draw()
{
	textManager->GenerateText("Player " + std::to_string(playerID[0]) +" Score: " + std::to_string(playerScores[0]) + 
		"    Player " + std::to_string(playerID[1]) + " Score: " + std::to_string(playerScores[1]) + 
		"    Player " + std::to_string(playerID[2]) + " Score: " + std::to_string(playerScores[2]) + 
		"    Player " + std::to_string(playerID[3]) + " Score: " + std::to_string(playerScores[3]) + 
		"    Time: " + std::to_string(time) + 
		"    GameState: " + currentGameState
		, 10, 565);
	textManager->DrawText();

	textManager1->GenerateText("Player " + std::to_string(playerID[0]) + " RoundtripTime: " + std::to_string(playerPing[0]) +
		"    Player " + std::to_string(playerID[1]) + " RoundtripTime: " + std::to_string(playerPing[1]) +
		"    Player " + std::to_string(playerID[2]) + " RoundtripTime: " + std::to_string(playerPing[2]) +
		"    Player " + std::to_string(playerID[3]) + " RoundtripTime: " + std::to_string(playerPing[3])
		, 10, 600);

	textManager1->DrawText();
}

bool HUD::SetPlayerScore(int p_index, int p_value)
{
	if (p_index < playerScores.size())
	{
		playerScores[p_index] = p_value;
		return true;
	}
	return false;
}

bool HUD::SetPlayerID(int p_index, int p_value)
{
	if (p_index < playerID.size())
	{
		playerID[p_index] = p_value;
		return true;
	}
	return false;
}

bool HUD::SetPlayerPing(int p_index, int p_value)
{
	if (p_index < playerPing.size())
	{
		playerPing[p_index] = p_value;
		return true;
	}
	return false;
}


void HUD::SetTime(int p_value)
{
	time = p_value;
}

void HUD::Update(float p_delta)
{
}