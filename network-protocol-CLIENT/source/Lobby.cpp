#include "stdafx.h"
#include "Lobby.h"
#include "ServiceLocator.h"
#include "ButtonManager.h"
#include <functional>
#include "HUD.h"
#include "GameRunner.h"
#include "TextString.h"

Lobby::Lobby()
{	
	buttonManager = new ButtonManager();
	isInGame = false;
	buttonManager->AddButton("Assets/Play.bmp","Assets/PlaySelected.bmp",100,100,100,100,true,std::bind(&Lobby::ConnectOrDisconnect, this ));
	buttonManager->AddButton("Assets/Quit.bmp", "Assets/QuitSelected.bmp", 100, 100, 100, 250, false, std::bind(&Lobby::Quit, this ));	
	hud = new HUD();
	gameRunner = ServiceLocator<GameRunner>::GetService();
	
}
void Lobby::Enter()
{
	isInGame = false;
	buttonManager = new ButtonManager();
	buttonManager->AddButton("Assets/Play.bmp", "Assets/PlaySelected.bmp", 100, 100, 100, 100, true, std::bind(&Lobby::ConnectOrDisconnect, this));
	buttonManager->AddButton("Assets/Quit.bmp", "Assets/QuitSelected.bmp", 100, 100, 100, 250, false, std::bind(&Lobby::Quit, this));
	textMessage = new TextString();
}

void Lobby::Exit()
{
	delete buttonManager;
	buttonManager = nullptr;

	gameRunner = nullptr;
}

void Lobby::Quit()
{
	gameRunner->SetIsRunning(false);

}

void Lobby::ConnectOrDisconnect()
{
		isInGame = true;
}

void Lobby::Update(uint8_t p_delta)
{
	buttonManager->Update((float)p_delta);
	textMessage->GenerateText("Use W and S to hover and Enter to select", 300, 100);
}

void Lobby::Draw()
{
	buttonManager->Draw();
	hud->Draw();
	textMessage->DrawText();
}


Lobby::~Lobby()
{
}

bool Lobby::GetIsInGame()
{
	return isInGame;
}