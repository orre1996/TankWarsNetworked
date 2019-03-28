#include "stdafx.h"
#include "DrawManager.h"
#include "Sprite.h"
#include "Constants.h"
#include "TextTexture.h"

DrawManager::DrawManager()
{
}

DrawManager::~DrawManager()
{
}

void DrawManager::Initialize()
{
	m_window = SDL_CreateWindow("Augustus", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 700, 0);
	assert(m_window != nullptr && "SDL_CreateWindow Failed");

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_VIDEO_OPENGL);
	assert(m_renderer != nullptr && "SDL_CreateRenderer Failed");

	//	Uint32 ColorKey = SDL_MapRGB(, 19.2f, 17.6f, 19.2f);


}

void DrawManager::Shutdown()
{
	SDL_DestroyWindow(m_window);
	m_window = nullptr;

	SDL_DestroyRenderer(m_renderer);
	m_renderer = nullptr;
}

void DrawManager::Clear()
{
	SDL_RenderClear(m_renderer);
}

void DrawManager::SetDrawColor(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	SDL_SetRenderDrawColor(m_renderer, p_r, p_g, p_b, p_a);
}
void DrawManager::Present()
{
	SDL_RenderPresent(m_renderer);
}

void DrawManager::Draw(Sprite* p_sprite, int p_x, int p_y)
{
	SDL_Rect dstRect = { p_x,p_y, p_sprite->GetSource().w, p_sprite->GetSource().h };
	SDL_RenderCopy(m_renderer, p_sprite->GetTexture(), &p_sprite->GetSource(), &dstRect);
}

void DrawManager::NewDraw(Sprite* p_sprite, int p_x, int p_y, float p_r, SDL_Point* Center, SDL_RendererFlip flip)
{
	SDL_Rect dstRect = { p_x,p_y, p_sprite->GetSource().w, p_sprite->GetSource().h };
	SDL_RenderCopyEx(m_renderer, p_sprite->GetTexture(), &p_sprite->GetSource(), &dstRect, p_r, Center, flip);
}

void DrawManager::DrawText(TextTexture& p_texture, const SDL_Rect& p_rect)
{
	SDL_RenderCopy(m_renderer, p_texture.getPointer(), NULL, &p_rect);
}

void DrawManager::DebugDraw(int p_x, int p_y, int p_w, int p_h)
{
	SDL_Rect rect = { p_x,p_y,p_w,p_h };
	SDL_RenderDrawRect(m_renderer, &rect);
}

void DrawManager::DebugDraw(SDL_Rect &p_rect)
{

}

void DrawManager::DebugDraw(SDL_Rect & p_rect, Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a)
{
	SaveDrawColor();
	SetDrawColor(p_r, p_g, p_b, p_a);
	SDL_RenderDrawRect(m_renderer, &p_rect);
	LoadDrawColor();
}

SDL_Renderer * DrawManager::GetRenderer()
{
	return m_renderer;
}

void DrawManager::SaveDrawColor()
{
	SDL_GetRenderDrawColor(m_renderer, &m_r, &m_g, &m_b, &m_a);
}

void DrawManager::LoadDrawColor()
{
	SDL_SetRenderDrawColor(m_renderer, m_r, m_g, m_b, m_a);
}
