#pragma once
class TextString;
#include <vector>
#include <map>
#include "protocol.h"

/*
struct bla
{
	std::map<int, std::string> gameStateMap;
};*/

class HUD
{
public:
	HUD();
	~HUD();
	
	void Draw();
	void Update(float p_delta);
	bool SetPlayerScore(int p_index, int p_value);
	bool SetPlayerID(int p_index, int p_value);
	bool SetPlayerPing(int p_index, int p_value);
	void SetTime(int p_time);
	void SetState(int p_state);

private:
	int time;
	TextString *textManager;
	TextString *textManager1;
	std::vector<int> playerScores;
	std::vector<int> playerID;
	std::vector<int> playerPing;
	std::map<int, std::string> gameStateMap;
	std::string currentGameState;
};

