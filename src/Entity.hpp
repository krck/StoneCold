
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

private:
	uint _xPos, _yPos;
	const int _width, _height;
	SDL_Rect _srcRect, _destRect;
	SDL_Renderer* _renderer;
	std::shared_ptr<SDL_Texture> _texture;
};

}

#endif
