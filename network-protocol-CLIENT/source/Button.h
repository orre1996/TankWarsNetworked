#pragma once
#include <string>
#include <functional>

class Sprite;
class SpriteManager;
class DrawManager;

class Button
{
public:
	Button(float p_x, float p_y, std::string p_spritePath, std::string p_spriteSelectedPath, float p_spriteWidth, float p_spriteHeight, bool p_isActivated,
		std::function<void()> p_callback);
	~Button();

	void OnUse();
	void SetActivated(bool p_activation);
	//void SetCallback(std::function<void()> p_callback);
	void Draw();

private:
	std::function<void()> callback;
	bool isActivated;
	SpriteManager* spriteManager;
	DrawManager* drawManager;
	float x;
	float y;
	Sprite* sprite;
	Sprite* selectedSprite;




};

