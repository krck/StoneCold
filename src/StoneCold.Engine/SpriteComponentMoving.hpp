
#ifndef STONECOLD_SPRITECOMPONENTMOVING_H
#define STONECOLD_SPRITECOMPONENTMOVING_H

#include "SDL_Base.hpp"
#include "Component.hpp"
#include "AnimationComponent.hpp"
#include "CollisionComponent.hpp"
#include "TransformComponent.hpp"

namespace StoneCold::Engine {

//
// 2D moving Sprite Component (Player Character, NPCs, ...)
// Required: TransformComponent
// Optional: CollisionComponent, AnimationComponent
//
// Contains information needed to render a 2D sprite (Texture, SDL_Renderer, ...)
// Needs a Entity with a TransformComponent to update the position on screen
//
class SpriteComponentMoving : public Component {
private:
	AnimationComponent* _animationComponent;
	CollisionComponent* _collisionComponent;
	TransformComponent* _transform;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Rect _srcRect;
	SDL_FRect _destRect;
	SDL_RendererFlip _flip;

public:
	SpriteComponentMoving(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_FRect destRect)
		: _renderer(renderer), _texture(texture), _srcRect(srcRect), _destRect(destRect), _flip(SDL_RendererFlip::SDL_FLIP_NONE)
		, _animationComponent(nullptr), _collisionComponent(nullptr), _transform(nullptr) { }

	void Init(Entity* entity) override {
		Component::Init(entity);

		// Get the TransformComponent to read transformations based on the Keyboard input
		_transform = _entity->GetComponent<TransformComponent>();

		// Get the AnimationComponent (if it has one) to get the current framePosition, aka. _srcRect
		if (_entity->HasComponent<AnimationComponent>())
			_animationComponent = _entity->GetComponent<AnimationComponent>();

		// Get the CollisionComponent (if it has one) to keep it up to date with the movement, aka. _destRect
		if (_entity->HasComponent<CollisionComponent>())
			_collisionComponent = _entity->GetComponent<CollisionComponent>();
	}

	void Update(uint32 frameTime) override {
		// Update the Sprite position on screen based on the transformations
		_destRect.x = _transform->Position.X;
		_destRect.y = _transform->Position.Y;
		_destRect.w = _transform->Dimensions.X * _transform->Scale;
		_destRect.h = _transform->Dimensions.Y * _transform->Scale;

		// Update the Collision CollisionBox, based on the new position
		if (_collisionComponent != nullptr) {
			if (_collisionComponent->HasHitbox()) {
				// Centering the Hitbox within the actual _destRect to get the CollisionBox (Only works with smaller Hitboxes)
				auto xOffset = floorf((_destRect.w - (_collisionComponent->Hitbox.X * _transform->Scale)) / 2.f);
				auto yOffset = floorf((_destRect.h - (_collisionComponent->Hitbox.Y * _transform->Scale)) / 2.f);
				_collisionComponent->CollisionBox = {
					_destRect.x + xOffset,
					_destRect.y + yOffset,
					_collisionComponent->Hitbox.X * _transform->Scale,
					_collisionComponent->Hitbox.Y * _transform->Scale,
				};
			}
			else {
				_collisionComponent->CollisionBox = _destRect;
			}
		}
	}

	void Render(SDL_FRect camera) override {
		// If the Sprite is Animated, get the current Source rectangle (frame inside the texture) based on the Animation
		if (_animationComponent != nullptr) {
			_srcRect = _animationComponent->GetCurrentAnimationFrame();
			_flip = (_transform->Velocity.X == 0 ? _flip : (_transform->Velocity.X < 0 ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE));
		}

		// Get the Destination rectangle (render position on screen) relative to the camera
		SDL_FRect currentDest = { _destRect.x - camera.x, _destRect.y - camera.y, _destRect.w, _destRect.h };

		// Add Sprite to the SDL Renderer
		SDL_RenderCopyExF(_renderer, _texture, &_srcRect, &currentDest, 0, nullptr, _flip);
	}

};

}

#endif
