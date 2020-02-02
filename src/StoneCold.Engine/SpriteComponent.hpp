
#ifndef STONECOLD_SPRITECOMPONENT_H
#define STONECOLD_SPRITECOMPONENT_H

#include "SDL_Base.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"

namespace StoneCold::Engine {

//
// 2D Sprite Component
// Dependent on: TransformComponent
//
// Contains information needed to render a 2D sprite (Texture, SDL_Renderer, ...)
// Needs a GameObject with a TransformComponent to update the position on screen
//
class SpriteComponent : public IComponent {
private:
	TransformComponent* _transform;
	SDL_Renderer* _renderer;
	SDL_Texture* _texture;
	SDL_Rect _srcRect, _destRect;

public:
	SpriteComponent(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect destRect)
		: _renderer(renderer), _texture(texture), _srcRect(srcRect), _destRect(destRect) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
		// Get the TransformComponent to read transformations based on the Keyboard input
		_transform = _gameObject->GetComponent<TransformComponent>();

		_srcRect.x = 0;
		_srcRect.y = 0;
		_srcRect.w = _transform->Dimensions.X;
		_srcRect.h = _transform->Dimensions.Y;
	}

	void Update(uint timestampOld, uint timestampNew) override {
		_destRect.x = (int)_transform->Position.X;
		_destRect.y = (int)_transform->Position.Y;
		_destRect.w = _transform->Dimensions.X * _transform->Scale;
		_destRect.h = _transform->Dimensions.Y * _transform->Scale;
	}

	void Render() override {
		// Use SDL_RenderCopyEx in case of Animation
		SDL_RenderCopy(_renderer, _texture, &_srcRect, &_destRect);
	}
};

}

#endif
