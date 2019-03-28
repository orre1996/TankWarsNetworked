#include "stdafx.h"
#include "FontManager.h"

FontManager::FontManager(const std::string& p_string, int p_size)
{
	_font = TTF_OpenFont(p_string.c_str(), p_size);
	SDL_assert(_font != nullptr);
}


FontManager::~FontManager()
{
	TTF_CloseFont(_font);
	_font = nullptr;
}

TTF_Font* FontManager::getPointer() const
{
	return _font;
}
