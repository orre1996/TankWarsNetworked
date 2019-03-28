#include "stdafx.h"
#include "Keyboard.h"

Keyboard::Keyboard() :
	m_keys{}, 
	m_keysPrevious{}
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::SetKey(SDL_Scancode p_key, bool p_value)
{
	m_keys[p_key] = p_value;
}

bool Keyboard::GetKeyDown(SDL_Scancode p_key)
{
	return m_keys[p_key];
}

bool Keyboard::GetKeyDownOnce(SDL_Scancode p_key)
{
	return (m_keysPrevious[p_key] == false && m_keys[p_key] == true);
}

void Keyboard::Update()
{
	for (int i = 0; i < 5; i++)
	{
		m_keysPrevious[i] = m_keys[i];
	}
}