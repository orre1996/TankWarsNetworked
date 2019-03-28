#pragma once

class Sprite;
class TextTexture;

class DrawManager
{
public:
	DrawManager();
	~DrawManager();
	void Initialize(); // Create window + renderer
	void Shutdown();   // delete window + renderer
	void Clear();
	void SetDrawColor(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a);      // use sdl functionality to clear
	void Present();    //         -||-          to present
	void Draw(Sprite* p_sprite, int p_x, int p_y); // -||- to rendercopy
	void NewDraw(Sprite* p_sprite, int p_x, int p_y, float p_r, SDL_Point* Center, SDL_RendererFlip flip);
	void DebugDraw(int p_x, int p_y, int p_w, int p_h); // -||- to drawrect
	void DebugDraw(SDL_Rect &p_rect);
	void DebugDraw(SDL_Rect &p_rect, Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a);
	void DrawText(TextTexture& p_texture, const SDL_Rect& p_rect);

	SDL_Renderer* GetRenderer();
private:
	void SaveDrawColor();
	void LoadDrawColor();
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	Uint8 m_r;
	Uint8 m_g;
	Uint8 m_b;
	Uint8 m_a;

};



