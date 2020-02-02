
#include "Sprite.hpp"

using namespace StoneCold::Engine;

Sprite::Sprite(SDL_Renderer* renderer, SDL_Texture* texture, int width, int height)
	: Entity(renderer), _texture(texture), _width(width), _height(height) {
	_srcRect = { 0, 0, width, height };
	_destRect = { 0, 0, width, height };
}

void Sprite::Update(uint timestampOld, uint timestampNew) {
	_destRect.y += (velocity_Y * 5);
	_destRect.x += (velocity_X * 5);
}

void Sprite::Render() {
	// Use SDL_RenderCopyEx ??
	SDL_RenderCopy(_renderer, _texture, &_srcRect, &_destRect);
}
