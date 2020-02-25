
#ifndef STONECOLD_SPRITECOMPONENTFIXED_H
#define STONECOLD_SPRITECOMPONENTFIXED_H

#include "SDL_Base.hpp"
#include "Component.hpp"

namespace StoneCold::Engine {

//
// 2D fixed Sprite Component (Map Tiles, Ground-Clutter, ...)
// Required: ---
// Optional: ---
//
// Contains information needed to render a 2D sprite (Texture, SDL_Renderer, ...)
// This is not updated, so the GameObject has to pass a fixed srcRect and destRect
//
class SpriteComponentFixed : public IComponent {
private:
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	const SDL_Rect _srcRect;
	const SDL_FRect _destRect;
	const SDL_RendererFlip _flip;

public:
	SpriteComponentFixed(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_FRect destRect, SDL_RendererFlip flip)
		: _renderer(renderer), _texture(texture), _srcRect(srcRect), _destRect(destRect), _flip(flip) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
	}

	void Render(SDL_FRect camera) override {
		// Get the Destination rectangle (render position on screen) relative to the camera (as int)
		SDL_Rect currentDest = {
			static_cast<int>(floorf(_destRect.x - camera.x)),
			static_cast<int>(floorf(_destRect.y - camera.y)),
			static_cast<int>(floorf(_destRect.w)),
			static_cast<int>(floorf(_destRect.h))
		};

		// Add Sprite to the SDL Renderer
		SDL_RenderCopyEx(_renderer, _texture, &_srcRect, &currentDest, 0, nullptr, _flip);
	}
};

}

#endif
