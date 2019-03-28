#include "stdafx.h"
#include "Mouse.h"

Mouse::Mouse() : m_buttons{}, m_buttonsPrevious{}, m_motion{}, m_position{}
{
}


Mouse::~Mouse()
{
}

bool Mouse::GetButtonDown(Uint8 p_index)
{
	if (p_index > 4)
		return false;

	return m_buttons[p_index];
}

bool Mouse::GetButtonPressed(Uint8 p_index)
{
	if (p_index > 4)
		return false;

	return (m_buttonsPrevious[p_index] == false
		&& m_buttons[p_index] == true);
}

bool Mouse::GetButtonReleased(Uint8 p_index)
{
	if (p_index > 4)
		return false;

	return (m_buttonsPrevious[p_index] == true
		&& m_buttons[p_index] == false);
}

void Mouse::SetButton(Uint8 p_button, bool p_value)
{
	m_buttons[p_button - 1] = p_value;
}

SDL_Point Mouse::GetPosition()
{
	return m_position;
}

SDL_Point Mouse::GetMotion()
{
	return m_motion;
}


void Mouse::SetMotion(SDL_MouseMotionEvent p_event)
{
	m_position.x = p_event.x;
	m_position.y = p_event.y;
	m_motion.x = p_event.xrel;
	m_motion.y = p_event.y;
}

void Mouse::Update()
{
	for (int i = 0; i < 5; i++)
	{
		m_buttonsPrevious[i] = m_buttons[i];
	}
	m_motion.x = 0;
	m_motion.y = 0;
}