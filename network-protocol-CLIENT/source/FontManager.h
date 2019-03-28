#pragma once
#include <string>
/*Code written by Robin Gerndt and Patrik Selleby based on code by Ulf Benjaminsson
Original source: Pong Assignment.
*/

class FontManager
{
	TTF_Font* _font;
public:
	FontManager(const std::string& p_string, int size);
	~FontManager();
	TTF_Font* getPointer() const;
};

