#pragma once

class Sprite;
class DrawManager;
class SpriteManager;

class IDrawable
{
public:
	IDrawable();
	virtual ~IDrawable();
	virtual void Draw() = 0;
protected:
	Sprite* m_Sprite = nullptr;
	Sprite* m_TankSprite = nullptr;
	Sprite* m_TurretSprite = nullptr;
	Sprite* m_TurretPipeSprite = nullptr;
	DrawManager* m_drawManager = nullptr;
	SpriteManager* m_spriteManager = nullptr;
};