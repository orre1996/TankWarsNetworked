#pragma once
#include <string>
#include <vector>
#include "ServiceLocator.h"
#include <functional>

class InputManager;
class SpriteManager;
class DrawManager;
class Sprite;
class Button;

class ButtonManager
{
public:
	ButtonManager();
	~ButtonManager();

	std::vector <Button*> buttons;

	void AddButton(std::string p_path,std::string p_pathSelected, float p_spriteWidth, float p_spriteHeight, float x, float y, bool isActivated, std::function<void()> p_callback);
	void Cycle(float p_delta);
	void Update(float p_delta);
	void Draw();
	


private:
	float inputTimer;
	float inputTimerCurrent;
	int currentButtonIndex;
	InputManager* inputManager;
	DrawManager* drawManager;
	SpriteManager* spriteManager;
	float x;
	float y;
	float initialCooldown;
	Sprite* sprite;

};
