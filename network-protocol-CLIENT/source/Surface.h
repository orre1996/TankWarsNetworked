#pragma once
#include <string>
/*Code written by Robin Gerndt and Patrik Selleby based on code by Ulf Benjaminsson
Original source: Pong Assignment.
*/


struct SDL_Surface;
class FontManager;
struct SDL_Color;
struct SDL_Rect;

class Surface
{
	Surface(const Surface&) = delete;
	Surface& operator = (Surface&) = delete;
	SDL_Surface* _surface;

public:
	Surface(const FontManager& p_font, const std::string& p_string, const SDL_Color& p_color);
	Surface();
	~Surface();
	SDL_Surface* getPointer() const;
	void getBounds(SDL_Rect& p_rect, int p_x, int p_y);
};

