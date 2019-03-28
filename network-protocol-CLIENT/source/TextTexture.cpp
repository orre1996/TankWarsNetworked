#include "stdafx.h"
#include "TextTexture.h"
#include "DrawManager.h"

TextTexture::TextTexture(const Surface& surface) {
	
	m_drawManager = ServiceLocator<DrawManager>::GetService();
	if (_textTexture == nullptr)
	{
		_textTexture = SDL_CreateTextureFromSurface(m_drawManager->GetRenderer(), surface.getPointer());
		SDL_assert(_textTexture != nullptr);
	}
}

void TextTexture::updateTexture(const Surface& surface)
{
	if (_textTexture != nullptr)
	{
		SDL_DestroyTexture(_textTexture);
	}
	_textTexture = SDL_CreateTextureFromSurface(m_drawManager->GetRenderer(), surface.getPointer());
	SDL_assert(_textTexture != nullptr);
}

TextTexture::~TextTexture() {
	if (_textTexture != nullptr) {
		SDL_DestroyTexture(_textTexture);
		_textTexture = nullptr;
	}
}
SDL_Texture* TextTexture::getPointer() const {
	return _textTexture;
}