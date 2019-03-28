#include "stdafx.h"
#include "InputManager.h"
#include "Mouse.h"
#include "Keyboard.h"
#include <iostream>

InputManager::InputManager()
{
	m_mouse = nullptr;
	m_keyboard = nullptr;

}

InputManager::~InputManager()
{
}

void InputManager::Initialize()
{
	m_mouse = new Mouse();
	m_keyboard = new Keyboard();
}

void InputManager::Shutdown()
{
	delete m_mouse;
	m_mouse = nullptr;
	delete m_keyboard;
	m_keyboard = nullptr;
}

SDL_Point InputManager::GetMousePosition()
{
	return m_mouse->GetPosition();
}

SDL_Point InputManager::GetMouseMotion()
{
	return m_mouse->GetMotion();
}

bool InputManager::IsMouseButtonDown(int p_button)
{
	return m_mouse->GetButtonDown(p_button);
}

bool InputManager::IsMouseButtonPressed(int p_button)
{
	return m_mouse->GetButtonPressed(p_button);
}

bool InputManager::IsMouseButtonReleased(int p_button)
{
	return m_mouse->GetButtonReleased(p_button);
}

bool InputManager::IsKeyDown(SDL_Scancode p_key)
{
	return m_keyboard->GetKeyDown(p_key);
}

bool InputManager::IsKeyDownOnce(SDL_Scancode p_key)
{
	return m_keyboard->GetKeyDownOnce(p_key);
}

void InputManager::HandleEvent(SDL_Event &event)
{
		if (event.type == SDL_KEYDOWN)
		{
			m_keyboard->SetKey(event.key.keysym.scancode, true);
		}
		else if (event.type == SDL_KEYUP)
		{
			m_keyboard->SetKey(event.key.keysym.scancode, false);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			m_mouse->SetButton(event.button.button, true);
		}
		else if (event.type == SDL_MOUSEBUTTONUP)
		{
			m_mouse->SetButton(event.button.button, false);
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			m_mouse->SetMotion(event.motion);
		}

}

void InputManager::Update()
{
	m_mouse->Update();
	m_keyboard->Update();

}

uint8_t InputManager::GetInput()
{
	uint8_t input = 0;

	if (IsKeyDown(SDL_SCANCODE_W))
		input += 1;
	if (IsKeyDown(SDL_SCANCODE_A))
		input += 2;
	if (IsKeyDown(SDL_SCANCODE_S))
		input += 4;
	if (IsKeyDown(SDL_SCANCODE_D))
		input += 8;

	if (IsMouseButtonDown(0))
	{
		input += 16;
	}

	return input;
}


