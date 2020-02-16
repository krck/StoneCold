
#ifndef STONECOLD_SPRITECOMPONENTANIMATED_H
#define STONECOLD_SPRITECOMPONENTANIMATED_H

#include "SDL_Base.hpp"
#include "Component.hpp"
#include "AnimationResource.hpp"
#include "CollisionComponent.hpp"
#include "TransformComponent.hpp"

namespace StoneCold::Engine {

//
// 2D animated Sprite Component (Player Character, NPCs, ...)
// Dependent on: TransformComponent (and can have a CollisionComponent)
//
// Contains information needed to render a 2D sprite (Texture, SDL_Renderer, ...)
// Needs a GameObject with a TransformComponent to update the position on screen
//
class SpriteComponentAnimated : public IComponent {
private:
	const std::unordered_map<std::string, StoneCold::Resources::Animation>& _animations;
	const StoneCold::Resources::Animation* _currentAnimation;
	SDL_Rect _currentFrame;
	uint _timeElapsed;
	int _currentFrameIndex;
	SDL_RendererFlip _flip;
	
	CollisionComponent* _collisionComponent;
	TransformComponent* _transform;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_FRect _destRect; // floats, because all Transformations are float calculations

public:
	SpriteComponentAnimated(SDL_Renderer* renderer, SDL_Texture* texture, const std::unordered_map<std::string, StoneCold::Resources::Animation>& animations, SDL_FRect destRect)
		: _collisionComponent(nullptr), _transform(nullptr), _renderer(renderer), _texture(texture), _animations(animations), _destRect(destRect) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
		// Get the TransformComponent to read transformations based on the Keyboard input
		_transform = _gameObject->GetComponent<TransformComponent>();
		// Get the CollisionComponent (if it has one) to keep it up to date with the _destRect
		if (gameObject->HasComponent<CollisionComponent>())
			_collisionComponent = gameObject->GetComponent<CollisionComponent>();
	}

	void Update(uint frameTime) override {
		// Update the Sprite position on screen
		_destRect.x = _transform->Position.X;
		_destRect.y = _transform->Position.Y;
		_destRect.w = _transform->Dimensions.X * _transform->Scale;
		_destRect.h = _transform->Dimensions.Y * _transform->Scale;
		
		// Update the Collision "box"
		if (_collisionComponent != nullptr) {
			_collisionComponent->CollisionDimensions = _destRect;
		}

		// Udpate the Sprites animation frame
		_timeElapsed += frameTime;
		if (_timeElapsed > _currentAnimation->FrameTime) {
			_timeElapsed -= _currentAnimation->FrameTime;
			_currentFrameIndex = (_currentFrameIndex < _currentAnimation->FrameCount ? _currentFrameIndex + 1 : 0);
		}
	}

	void Render() override {
		_currentFrame = _currentAnimation->FramePositions[_currentFrameIndex];

		// Use SDL_RenderCopyEx and flip the Animation, based on the last input velocity
		_flip = (_transform->Velocity.X == 0 ? _flip : (_transform->Velocity.X < 0 ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE));
		SDL_RenderCopyExF(_renderer, _texture, &_currentFrame, &_destRect, 0, nullptr, _flip);
	}
	
	void SetCurrentAnimation(const std::string& name) {
		_currentAnimation = &_animations.find(name)->second;
		if (_currentFrameIndex > _currentAnimation->FrameCount)
			_currentFrameIndex = 0;
	}
};

}

#endif
