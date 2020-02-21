
#ifndef STONECOLD_SPRITECOMPONENTFIXED_H
#define STONECOLD_SPRITECOMPONENTFIXED_H

#include "SDL_Base.hpp"
#include "Component.hpp"

namespace StoneCold::Engine {

//
// 2D moving Sprite Component (Map Tiles, Ground-Clutter, ...)
// Dependent on: --- (But can have a CollisionComponent)
//
// Contains information needed to render a 2D sprite (Texture, SDL_Renderer, ...)
// Needs a GameObject and a fixed position and size of where it is located
//
class SpriteComponentFixed : public IComponent {
private:
	CollisionComponent* _collisionComponent;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Rect _srcRect;
	SDL_FRect _destRect;
	SDL_RendererFlip _flip;
	int _scale = 1;

public:
	SpriteComponentFixed(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_FRect destRect, SDL_RendererFlip flip, int scale)
		: _collisionComponent(nullptr), _renderer(renderer), _texture(texture), _srcRect(srcRect), _destRect(destRect), _flip(flip), _scale(scale) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);

		// Set the CollisionDimensions once, if it needs any 
		if (gameObject->HasComponent<CollisionComponent>()) {
			_collisionComponent = gameObject->GetComponent<CollisionComponent>();
			_collisionComponent->CollisionDimensions = _destRect;
		}
	}

	void Render(SDL_FRect camera) override {
		// Get the dest rect relative to the camera position as int
		SDL_Rect currentDest = { 
			(int)floorf(_destRect.x - camera.x), 
			(int)floorf(_destRect.y - camera.y),
			(int)floorf(_destRect.w * _scale),
			(int)floorf(_destRect.h * _scale)
		};
		SDL_RenderCopyEx(_renderer, _texture, &_srcRect, &currentDest, 0, nullptr, _flip);
	}
};

}

#endif
