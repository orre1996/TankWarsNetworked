#include "stdafx.h"
#include "ButtonManager.h"
#include "Button.h"
#include "DrawManager.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "InputManager.h"
#include "ServiceLocator.h"
#include <algorithm>

class SpriteManager;

ButtonManager::ButtonManager()
{
	currentButtonIndex = 0;
	inputManager = ServiceLocator<InputManager>::GetService();
	spriteManager = ServiceLocator<SpriteManager>::GetService();
	//sprite = spriteManager->CreateSprite("Assets/preview.bmp", 177, 110, 35, 35);
	inputTimerCurrent = 0.0f;
	inputTimer = 500.0f;
	initialCooldown = 1000.0f;
}


ButtonManager::~ButtonManager()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
		buttons[i] = nullptr;
	}
	buttons.erase(std::remove(buttons.begin(), buttons.end(), nullptr), buttons.end());
}

void ButtonManager::AddButton(std::string p_path, std::string p_pathSelected, float p_spriteWidth, float p_spriteHeight, float x, float y, bool isActivated, std::function<void()> p_callback)
{
	//std::bind(&Class::Function, objectToInvokeFunction);
	Button* button = new Button(x, y, p_path, p_pathSelected, p_spriteWidth, p_spriteHeight, isActivated, p_callback);
	buttons.push_back(button);
}

void ButtonManager::Cycle(float p_delta)
{
	if (inputTimerCurrent == 0.0f)
	{
		if (inputManager->IsKeyDown(SDL_SCANCODE_W))
		{
			buttons[currentButtonIndex]->SetActivated(false);
			currentButtonIndex++;
		}
		else if (inputManager->IsKeyDown(SDL_SCANCODE_S))
		{
			buttons[currentButtonIndex]->SetActivated(false);
			currentButtonIndex--;
		}
		if (currentButtonIndex >= (int)buttons.size())
		{
			currentButtonIndex = 0;
		}
		if (currentButtonIndex < 0)
		{
			currentButtonIndex = (int)buttons.size() - 1;
		}
		buttons[currentButtonIndex]->SetActivated(true);
	}
	else
	{
		if (inputTimerCurrent >= inputTimer)
		{
			inputTimerCurrent -= inputTimer;

			if (inputManager->IsKeyDown(SDL_SCANCODE_W))
			{
				buttons[currentButtonIndex]->SetActivated(false);
				currentButtonIndex++;
			}
			else if (inputManager->IsKeyDown(SDL_SCANCODE_S))
			{
				buttons[currentButtonIndex]->SetActivated(false);
				currentButtonIndex--;
			}
			if (currentButtonIndex >= (int)buttons.size())
			{
				currentButtonIndex = 0;
			}
			if (currentButtonIndex < 0)
			{
				currentButtonIndex = (int)buttons.size() - 1;
			}
			buttons[currentButtonIndex]->SetActivated(true);
		}
	}
	if (inputManager->IsKeyDown(SDL_SCANCODE_S) || inputManager->IsKeyDown(SDL_SCANCODE_W))
	{
		inputTimerCurrent += p_delta;
	}
	else
	{
		inputTimerCurrent = 0.0f;
	}

	if (initialCooldown <= 0.0f)
	{
		if (inputManager->IsKeyDown(SDL_SCANCODE_RETURN))
		{
			buttons[currentButtonIndex]->OnUse();
		}
	}
	initialCooldown -= p_delta;
}

void ButtonManager::Update(float p_delta)
{
	Cycle(p_delta);
}

void ButtonManager::Draw()
{
	for (int i = 0; i < buttons.size(); i++)
	{
		buttons[i]->Draw();
	}
}