#include "stdafx.h"
#include "StateMachine.h"
#include "IState.h"

StateMachine::StateMachine()
{
	m_currentState = nullptr;
}


StateMachine::~StateMachine()
{
	auto it = m_states.begin();
	while (it != m_states.end())
	{
		delete it->second;
		it->second = nullptr;
		it++;
	}
	m_currentState = nullptr;
	m_states.clear();

}

void StateMachine::Update(uint8_t p_delta)
{
	m_currentState->Update(p_delta);
}

void StateMachine::Draw()
{
	m_currentState->Draw();
}

void StateMachine::AddState(const std::string p_name, IState * p_state)
{
	auto it = m_states.find(p_name);
	if (it == m_states.end())
	{
		m_states.insert(std::pair<std::string, IState*>(p_name, p_state));
	}
}

void StateMachine::SetState(const std::string p_name)
{
	auto it = m_states.find(p_name);

	if (it->second != nullptr)
	{
		if (m_currentState != nullptr)
			m_currentState->Exit();
		m_currentState = it->second;
		m_currentState->Enter();
	}
}

IState* StateMachine::GetCurrentState()
{
	return m_currentState;
}


