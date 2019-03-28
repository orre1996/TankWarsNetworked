#pragma once
class Sprite
{
public:
	Sprite(SDL_Texture* p_texture, int p_x, int p_y, int p_w, int p_h);
	~Sprite();
	void SetSource(int p_x, int p_y, int p_w, int p_h);
	SDL_Rect GetSource();
	SDL_Texture* GetTexture();
private:
	Sprite();
	SDL_Texture* m_texture;
	SDL_Rect m_source; // Defines what part of the texture that should be drawn
};

