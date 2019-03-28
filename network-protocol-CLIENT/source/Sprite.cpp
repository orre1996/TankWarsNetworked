#include "stdafx.h"
#include "Sprite.h"


Sprite::Sprite() // Private
{
};

Sprite::Sprite(SDL_Texture* p_texture, int p_x, int p_y, int p_w, int p_h)
{
	m_texture = p_texture;
	SetSource(p_x, p_y, p_w, p_h);
};

Sprite::~Sprite()
{
};

void Sprite::SetSource(int p_x, int p_y, int p_w, int p_h)
{
	m_source.x = p_x;
	m_source.y = p_y;
	m_source.w = p_w;
	m_source.h = p_h;
}
SDL_Rect Sprite::GetSource()
{
	return m_source;
}
SDL_Texture * Sprite::GetTexture()
{
	return m_texture;
};
