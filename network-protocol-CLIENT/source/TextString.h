#pragma once
#include <vector>
#include "FontManager.h"
#include "TextTexture.h"

class DrawManager;

class TextString
{
public:

	void GenerateText(std::string p_text, int m_x, int m_y);
	void GenerateText();
	void DrawText();
	void SetText(std::string p_text);

	TextString();
	~TextString();

	DrawManager* m_drawManager;

	std::string GetText();

	void SetPosition(int p_x, int p_y);
	int GetX();
	int GetY();
private:
	std::string m_text;
	TextTexture m_textTexture;
	SDL_Rect m_rect;
	FontManager m_font;
	SDL_Color m_color;

	int m_x;
	int m_y;


};

