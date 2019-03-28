#include "stdafx.h"
#include "SubMenu.h"
#include "Sprite.h"
#include "ServiceLocator.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "InputManager.h"
#include "ButtonManager.h"
#include <iostream>
#include <functional>
#include "protocol.h"

SubMenu::SubMenu(bool& p_hasDisconnected) : hasDisconnected(p_hasDisconnected)
{
	buttonManager = new ButtonManager();
	inputManager = ServiceLocator<InputManager>::GetService();
	isActivated = false;
	buttonManager->AddButton("Assets/Quit.bmp", "Assets/Quit.bmp", 100, 100, 200, 100, true, std::bind(&SubMenu::DisconnectCallback, this));
	inputTimerCurrent = 0.0f;
	inputTimerMax = 50.0f;
}


SubMenu::~SubMenu()
{
	delete buttonManager;
}

void SubMenu::DisconnectCallback()
{
	std::cout << "Disconnect callback called from state connected. \n";
	hasDisconnected = true;
}

void SubMenu::Update(uint8_t p_delta) {
	if (inputTimerCurrent <= 0.0f)
	{
		if (inputManager->IsKeyDown(SDL_SCANCODE_ESCAPE))
		{
			isActivated = (isActivated == false) ? true : false;
			inputTimerCurrent = inputTimerMax;
		}
	}

	if (inputTimerCurrent > 0.0f && !inputManager->IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		inputTimerCurrent -= p_delta;
	}

	if (isActivated)
		buttonManager->Update(p_delta);
}

void SubMenu::Draw() {
	if (isActivated)
	{
		buttonManager->Draw();
	}

}