#pragma once
class Sprite;
class SpriteManager;
class DrawManager;
class InputManager;
class ButtonManager;

class SubMenu
{
public:
	SubMenu(bool& p_hasDisconnected);
	~SubMenu();

	void Draw();
	void Update(uint8_t p_delta);

private:
	bool isActivated;
	bool& hasDisconnected;
	void DisconnectCallback();
	uint8_t inputTimerMax;
	uint8_t inputTimerCurrent;

	Sprite* menuSprite;
	SpriteManager* spriteManager;
	DrawManager* drawManager;
	InputManager* inputManager;
	ButtonManager* buttonManager;
};