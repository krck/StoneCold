
#ifndef STONECOLD_KEYBOARDCOMPONENT_H
#define STONECOLD_KEYBOARDCOMPONENT_H

#include "SDL_Base.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"
#include "SpriteComponentAnimated.hpp"

#include <iostream>
#include <string>

namespace StoneCold::Engine {

//
// Keyboard (Input) Controller
// Dependent on: TransformComponent and SpriteComponentAnimated
//
// Contains logic to process any Keyboard input based on SDL_Events
// Needs a GameObject with a TransformComponent to store the updates
// 
class KeyboardComponent : public IComponent {
private:
	TransformComponent* _transform;
	SpriteComponentAnimated* _spriteAnimation;
	bool _isAnimated;

public:
	KeyboardComponent() : _transform(nullptr), _spriteAnimation(nullptr), _isAnimated(false) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
		// Get the TransformComponent to write transformations based on the Keyboard input
		_transform = _gameObject->GetComponent<TransformComponent>();
		// Try to get the SpriteComponentAnimated to play different animations for different actions
		if (_gameObject->HasComponent<SpriteComponentAnimated>()) {
			_spriteAnimation = _gameObject->GetComponent<SpriteComponentAnimated>();
			_isAnimated = true;
		}
	}

	void HandleEvent(const uint8* keyStates) override {
		// For each keykeyStates contains a value of 1 if pressed and a value of 0 if not pressed
		// Add negative and positive velocity so the sprite doesn't move if both are pressed at the same time
		_transform->Velocity.Y = (-1.0f * keyStates[SDL_SCANCODE_UP]) + keyStates[SDL_SCANCODE_DOWN];
		_transform->Velocity.X = (-1.0f * keyStates[SDL_SCANCODE_LEFT]) + keyStates[SDL_SCANCODE_RIGHT];

		if (_isAnimated) {
			if (_transform->Velocity.Y > 0 || _transform->Velocity.X) {
				_spriteAnimation->SetCurrentAnimation("walk");
			}
			else {
				_spriteAnimation->SetCurrentAnimation("idle");
			}
		}
	}
};

}

#endif
