#pragma once
#include <string>
#include "IState.h"


class HUD;
class InputManager;
class DrawManager;
class SpriteManager;
class ButtonManager;
class Button;
class GameRunner;
class TextString;

class Lobby : public IState
{
public:
	Lobby();
	~Lobby();
	void Enter();
	void Exit();
	void Update(uint8_t p_delta);
	void Draw();
	void ConnectOrDisconnect();
	bool GetIsInGame();
	void Quit();
private:
	GameRunner* gameRunner;
	HUD* hud;
	bool isInGame;
	InputManager* inputManager;
	DrawManager* drawManager;
	SpriteManager* spriteManager;
	ButtonManager* buttonManager;
	TextString* textMessage;
};

