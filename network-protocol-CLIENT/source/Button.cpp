#include "stdafx.h"
#include "Button.h"
#include "ServiceLocator.h"
#include <iostream>
#include "SpriteManager.h"
#include "DrawManager.h"
#include "Sprite.h"


Button::Button(float p_x, float p_y, std::string p_spritePath, std::string p_spriteSelectedPath, float p_spriteWidth, float p_spriteHeight, bool p_isActivated,
	std::function<void()> p_callback)
{
	x = p_x;
	y = p_y;
	drawManager = ServiceLocator<DrawManager>::GetService();
	spriteManager = ServiceLocator<SpriteManager>::GetService();
	isActivated = p_isActivated;

	sprite = spriteManager->CreateSprite(p_spritePath, 0, 0, p_spriteWidth,p_spriteHeight/*p_spriteWidth, p_spriteHeight*/);
	selectedSprite = spriteManager->CreateSprite(p_spriteSelectedPath,0,0,p_spriteWidth,p_spriteHeight);
	callback = p_callback;
	//std::cout << "Button constructor called! \n";
}
Button::~Button()
{
}
void Button::SetActivated(bool p_activation)
{
	isActivated = p_activation;
}


void Button::OnUse()
{
	//do stuff.
	callback();
}

void Button::Draw()
{
	if (isActivated)
		drawManager->Draw(selectedSprite, x, y);
	else
		drawManager->Draw(sprite, x, y);
	//std::cout << "Button is drawin \n";
}

/*
void Button::SetCallback(std::function<void()> p_callback)
{
	callback = p_callback;
}*/
