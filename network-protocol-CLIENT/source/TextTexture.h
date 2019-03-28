#pragma once
/*Code written by Robin Gerndt and Patrik Selleby based on code by Ulf Benjaminsson
Original source: Pong Assignment.
*/

#include "ServiceLocator.h"

#include "Surface.h"
class DrawManager;

class TextTexture {
	TextTexture(const TextTexture&) = delete;
	TextTexture& operator=(TextTexture&) = delete;
	SDL_Texture* _textTexture;

public:
	TextTexture( const Surface& surface);
	void updateTexture( const Surface & surface);
	~TextTexture();

	DrawManager* m_drawManager;
	SDL_Texture* getPointer() const;
};