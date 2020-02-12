
#ifndef STONECOLD_SPRITECOMPONENT_H
#define STONECOLD_SPRITECOMPONENT_H

#include "SDL_Base.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"

namespace StoneCold::Engine {

//
// Animation contains only its name and an array of source rectangles (SDL_Rect srcRects) 
// to define which part of a full Texture image is part of the Animation / should be rendered
//
struct Animation {
public:
	Animation(const const std::vector<SDL_Rect>& framePositions, uint frameTime)
		: Name(name), FramePositions(framePositions), FrameCount(framePositions.size()), FrameTime(frameTime) {}
	
	const std::vector<SDL_Rect> FramePositions;
	const size_t FrameCount;
	const uint FrameTime;
};
	
//
// 2D animated Sprite Component
// Dependent on: TransformComponent
//
// Contains information needed to render a 2D sprite (Texture, SDL_Renderer, ...)
// Needs a GameObject with a TransformComponent to update the position on screen
//
class SpriteComponentAnimated : public IComponent {
private:
	const std::unordered_map<std::string, Animation> _animations;
	Animation _currentAnimation;
	SDL_Rect _currentFrame;
	uint _timeElapsed;
	int _currentFrameIndex;
	
	TransformComponent* _transform;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_FRect _destRect; // floats, because all Transformations are float calculations

public:
	SpriteComponentAnimated(SDL_Renderer* renderer, SDL_Texture* texture, const std::unordered_map<std::string, Animation>& animations, SDL_FRect destRect)
		: _transform(nullptr), _renderer(renderer), _texture(texture), _animations(animations), _destRect(destRect) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
		// Get the TransformComponent to read transformations based on the Keyboard input
		_transform = _gameObject->GetComponent<TransformComponent>();
	}

	void Update(uint frameTime) override {
		// Update the Sprite position on screen
		_destRect.x = _transform->Position.X;
		_destRect.y = _transform->Position.Y;
		_destRect.w = _transform->Dimensions.X * _transform->Scale;
		_destRect.h = _transform->Dimensions.Y * _transform->Scale;
		
		// Udpate the Sprites animation frame
		_timeElapsed += frameTime;
		if (_timeElapsed > _currentAnimation._frameTime) {
			_timeElapsed -= _currentAnimation._frameTime;
			_currentFrameIndex = (_currentFrameIndex < _currentAnimation.FrameCount ? _currentFrameIndex + 1 : 0);
		}
	}

	void Render() override {
		_currentFrame = _currentAnimation.FramePositions[_currentFrameIndex];

		// Use SDL_RenderCopyEx in case of Animation
		auto flip = (_transform->Velocity.X < 0 ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE);
		SDL_RenderCopyExF(_renderer, _texture, &_currentFrame, &_destRect, 0, nullptr, flip);
	}
	
	void SetCurrentAnimation(const std::string& name) {
		_currentAnimation = _animations[name];
	}
};

}

#endif
