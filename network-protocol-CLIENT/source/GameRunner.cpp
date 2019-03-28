#include "GameRunner.h"

GameRunner::GameRunner(bool p_isRunning)
{
	isRunning = p_isRunning;
}


GameRunner::~GameRunner()
{
}

void GameRunner::SetIsRunning(bool p_state)
{
	isRunning = p_state;
}

bool GameRunner::GetIsRunning()
{
	return isRunning;
}