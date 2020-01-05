
#ifndef STONECOLD_ENTITY_H
#define STONECOLD_ENTITY_H

#include "TextureManager.hpp"
#include <string>

namespace StoneCold {

class Entity {
public:
	Entity(SDL_Renderer* renderer, const std::string& textureFile, int texWidth, int texHeight);
	Entity(const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;

	void Update();
	void Render();

	int velocity_X, velocity_Y;

private:
	SDL_Renderer* _renderer;
	std::shared_ptr<SDL_Texture> _texture;
	const int _width, _height;
	// Rectangles to specify the source (inside the texture) and the destination (on the screen)
	SDL_Rect _srcRect, _destRect; 
};

}

#endif
