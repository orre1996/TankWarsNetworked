#pragma once
class GameRunner
{
public:
	GameRunner(bool p_isRunning);
	~GameRunner();

	bool GetIsRunning();
	void SetIsRunning(bool p_state);

private:
	bool isRunning;
};

