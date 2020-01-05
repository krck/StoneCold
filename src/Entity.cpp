
#include "Entity.hpp"

using namespace StoneCold;

Entity::Entity(SDL_Renderer* renderer, const std::string& textureFile, int texWidth, int texHeight) : _renderer(renderer), _width(texWidth), _height(texHeight) {
	_srcRect = { 0, 0, texWidth, texHeight };
	_destRect = { 0, 0, texWidth, texHeight };
	_texture = TextureManager::LoadTexture(renderer, textureFile);
}

void Entity::Update() {
	_destRect.y += (velocity_Y * 3);
	_destRect.x += (velocity_X * 3);
}

void Entity::Render() {
	SDL_RenderCopy(_renderer, _texture.get(), &_srcRect, &_destRect);
}
