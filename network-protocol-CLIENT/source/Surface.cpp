/*Code written by Robin Gerndt and Patrik Selleby based on code by Ulf Benjaminsson
Original source: Pong Assignment.
*/
#include "stdafx.h"
#include "Surface.h"
#include "FontManager.h"




Surface::~Surface()
{
	if (_surface != nullptr)
	{
		SDL_FreeSurface(_surface);
		_surface = nullptr;
	}
}

SDL_Surface* Surface::getPointer() const
{
	return _surface;
}


Surface::Surface(const FontManager& p_font, const std::string& p_string, const SDL_Color& p_color)
{
	_surface = TTF_RenderText_Solid(p_font.getPointer(), p_string.c_str(), p_color);
	if (_surface == nullptr)
	{
		throw std::runtime_error(TTF_GetError());
	}
}
Surface::Surface()
{
	_surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 32); //crap value
	if (_surface == nullptr)
	{
		throw std::runtime_error(TTF_GetError());
	}
}

void Surface::getBounds(SDL_Rect& p_rect, int p_x, int p_y) //should it not really be called setbounds?
{
	p_rect.h = _surface->h;
	p_rect.w = _surface->w;
	p_rect.x = p_x; /*- (p_rect.w / 2);*/ //i assume something else than this.
	p_rect.y = p_y;
}