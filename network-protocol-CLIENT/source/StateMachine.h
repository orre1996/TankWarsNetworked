#pragma once
//Class is based on Jerry Jonsson's implementation of a statemachine in his Augustus engine.

#include <string>
#include <map>

class IState;

class StateMachine
{
public:
	void Update(uint8_t p_delta);
	void Draw();
	void SetState(const std::string p_name);
	void AddState(const std::string p_name, IState * p_state);
	IState* GetCurrentState();
	StateMachine();
	~StateMachine();

private:
	std::map<std::string, IState*> m_states;
	IState* m_currentState;
};

