#pragma once
#include <map>
#include <vector>

class DrawManager;
class Sprite;

class SpriteManager
{
public:
	SpriteManager(SDL_Renderer* p_renderer);
	~SpriteManager();
	Sprite* CreateSprite(const std::string p_file, unsigned int p_x, unsigned int p_y, unsigned int p_w, unsigned int p_h);
	void DestroySprite(Sprite* p_sprite);


private:
	SpriteManager();
	SDL_Renderer* m_renderer;
	std::vector<Sprite*> m_sprites;
	std::map<std::string, SDL_Texture*> m_textures;
};

