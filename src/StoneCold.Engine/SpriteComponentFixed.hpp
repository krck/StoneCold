
#ifndef STONECOLD_SPRITECOMPONENTFIXED_H
#define STONECOLD_SPRITECOMPONENTFIXED_H

#include "SDL_Base.hpp"
#include "Component.hpp"

namespace StoneCold::Engine {

//
// 2D moving Sprite Component (Map Tiles, Ground-Clutter, ...)
// Dependent on: ---
//
// Contains information needed to render a 2D sprite (Texture, SDL_Renderer, ...)
// Needs a GameObject and a fixed position and size of where it is located
//
class SpriteComponentFixed : public IComponent {
private:
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Rect _srcRect;
	SDL_Rect _destRect;

public:
	SpriteComponentFixed(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
		: _renderer(renderer), _texture(texture), _srcRect(srcRect), _destRect(destRect) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
	}

	void Render() override {
		// Normal RenderCopy (not F), because no float transformation calculations take place
		SDL_RenderCopy(_renderer, _texture, &_srcRect, &_destRect);
	}
};

}

#endif
