
#ifndef STONECOLD_SPRITECOMPONENTMOVING_H
#define STONECOLD_SPRITECOMPONENTMOVING_H

#include "SDL_Base.hpp"
#include "Component.hpp"
#include "CollisionComponent.hpp"
#include "TransformComponent.hpp"

namespace StoneCold::Engine {

//
// 2D moving Sprite Component (Projectiles, ...)
// Dependent on: TransformComponent (and can have a CollisionComponent)
//
// Contains information needed to render a 2D sprite (Texture, SDL_Renderer, ...)
// Needs a GameObject with a TransformComponent to update the position on screen
//
class SpriteComponentMoving : public IComponent {
private:
	CollisionComponent* _collisionComponent;
	TransformComponent* _transform;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Rect _srcRect;
	SDL_FRect _destRect; // floats, because all Transformations are float calculations

public:
	SpriteComponentMoving(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_FRect destRect)
		: _collisionComponent(nullptr), _transform(nullptr), _renderer(renderer), _texture(texture), _srcRect(srcRect), _destRect(destRect) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
		// Get the TransformComponent to read transformations based on the Keyboard input
		_transform = _gameObject->GetComponent<TransformComponent>();
		// Get the CollisionComponent (if it has one) to keep it up to date with the _destRect
		if (gameObject->HasComponent<CollisionComponent>())
			_collisionComponent = gameObject->GetComponent<CollisionComponent>();

		_srcRect.x = 0;
		_srcRect.y = 0;
		_srcRect.w = (int)_transform->Dimensions.X;
		_srcRect.h = (int)_transform->Dimensions.Y;
	}

	void Update(uint frameTime) override {
		_destRect.x = _transform->Position.X;
		_destRect.y = _transform->Position.Y;
		_destRect.w = _transform->Dimensions.X * _transform->Scale;
		_destRect.h = _transform->Dimensions.Y * _transform->Scale;
		// Update the Collision "box"
		if (_collisionComponent != nullptr) {
			_collisionComponent->CollisionDimensions = _destRect;
		}
	}

	void Render() override {
		// Use SDL_RenderCopyEx in case of Animation
		SDL_RenderCopyF(_renderer, _texture, &_srcRect, &_destRect);
	}
};

}

#endif