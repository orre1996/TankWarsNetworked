#include "stdafx.h"
#include "TextString.h"

#include "ServiceLocator.h"
#include "DrawManager.h"
#include "Surface.h"

TextString::TextString() :
	m_font { "Assets/Font/OpenSans-Bold.ttf",14 },
	m_textTexture{ Surface() },
	m_color{ 255,255,255,255 },
	m_x{0},
	m_y{0},
	m_text{""}
{
	
	m_drawManager = ServiceLocator<DrawManager>::GetService();
}

void TextString::GenerateText(std::string p_text, int p_x, int p_y)
{
	m_text = p_text;
	Surface m_surface(m_font,m_text.c_str(), m_color);
	m_textTexture.updateTexture(m_surface);
	m_surface.getBounds(m_rect, p_x, p_y);
}

void TextString::GenerateText()
{
	Surface m_surface(m_font, m_text.c_str(), m_color);
	m_textTexture.updateTexture(m_surface);
	m_surface.getBounds(m_rect, m_x, m_y);
}

void TextString::SetText(std::string p_text)
{
	m_text = p_text;
}

void TextString::DrawText()
{
	m_drawManager->DrawText(m_textTexture, m_rect);
}

std::string TextString::GetText()
{
	return m_text;
}

int TextString::GetX()
{
	return m_x;
}

int TextString::GetY()
{
	return m_y;
}

void TextString::SetPosition(int p_x, int p_y)
{
	m_x = p_x;
	m_y = p_y;
}


TextString::~TextString()
{

}
