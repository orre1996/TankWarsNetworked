#include "stdafx.h"
#include "SpriteManager.h"
#include "Sprite.h"
#include "DrawManager.h"
#include <iostream>

SpriteManager::SpriteManager()
{
}

SpriteManager::SpriteManager(SDL_Renderer * p_renderer)
{
	m_renderer = p_renderer;
}

SpriteManager::~SpriteManager()
{
}

//server->client remote entity state.
//kill message
//timestamp.

Sprite * SpriteManager::CreateSprite(const std::string p_file, unsigned int p_x, unsigned int p_y,
	unsigned int p_w, unsigned int p_h)
{
	auto it = m_textures.find(p_file); // Returns an iterator to a pos or end, depending on success
	if (it == m_textures.end())
	{
		// If we do not find the texture we need to load it and inser it in to our std::map so
		// that we may create pointers to the same texture for several sprites.
		SDL_Surface* xSurface = SDL_LoadBMP(p_file.c_str());

		//SDL_SetColorKey(xSurface, SDL_TRUE, SDL_MapRGB(xSurface->format, 160, 64, 192));
		SDL_Texture* xTexture = SDL_CreateTextureFromSurface(m_renderer, xSurface);

		SDL_FreeSurface(xSurface);
		m_textures.insert(std::pair<std::string, SDL_Texture*>(p_file, xTexture));
		it = m_textures.find(p_file);

	}

	Sprite* xSprite = new Sprite(it->second, p_x, p_y, p_w, p_h);
	m_sprites.push_back(xSprite);
	return xSprite;
}

void SpriteManager::DestroySprite(Sprite * p_sprite)
{
	//TODO: iterate over the vector to find the specific sprite, if found, delete
}
