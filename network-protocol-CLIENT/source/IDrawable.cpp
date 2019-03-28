#include "stdafx.h"
#include "IDrawable.h"
#include "ServiceLocator.h"

IDrawable::IDrawable()
{
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	m_spriteManager = ServiceLocator<SpriteManager>::GetService();
}

IDrawable::~IDrawable()
{
	m_Sprite = nullptr;
	m_TankSprite = nullptr;
	m_TurretSprite = nullptr;
	m_TurretPipeSprite = nullptr;
	m_drawManager = nullptr;
	m_spriteManager = nullptr;
}
