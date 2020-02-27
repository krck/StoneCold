
#ifndef STONECOLD_KEYBOARDCOMPONENT_H
#define STONECOLD_KEYBOARDCOMPONENT_H

#include "SDL_Base.hpp"
#include "Entity.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"
#include "AnimationComponent.hpp"

#include <iostream>
#include <string>

namespace StoneCold::Engine {

//
// Keyboard (Input) Controller
// Required: TransformComponent
// Optional: AnimationComponent
//
// Contains logic to process any Keyboard input based on SDL_Events
// Needs a Entity with a TransformComponent to store the updates
// 
class KeyboardComponent : public Component {
private:
	TransformComponent* _transform;
	AnimationComponent* _animationComponent;

public:
	KeyboardComponent() : _transform(nullptr), _animationComponent(nullptr) { }

	void Init(Entity* entity) override {
		Component::Init(entity);

		// Get the TransformComponent to write transformations based on the Keyboard input
		_transform = _entity->GetComponent<TransformComponent>();

		// Try to get the AnimationComponent to play different animations for different actions
		if (_entity->HasComponent<AnimationComponent>()) {
			_animationComponent = _entity->GetComponent<AnimationComponent>();
		}
	}

	void HandleInputEvent(const std::vector<uint8>& keyStates) override {
		// For each keykeyStates contains a value of 1 if pressed and a value of 0 if not pressed
		// Add negative and positive velocity so the sprite doesn't move if both are pressed at the same time
		_transform->Velocity.Y = (-1.0f * keyStates[SDL_SCANCODE_W]) + keyStates[SDL_SCANCODE_S];
		_transform->Velocity.X = (-1.0f * keyStates[SDL_SCANCODE_A]) + keyStates[SDL_SCANCODE_D];

		// Debug "dash"
		_transform->Speed = (keyStates[SDL_SCANCODE_RCTRL] ? _transform->BaseSpeed * 3 : _transform->BaseSpeed);

		// Update/Play a different Animation, based on the current input
		if (_animationComponent != nullptr) {
			// Dash/Dodge movement
			if (_transform->Speed > _transform->BaseSpeed)
				_animationComponent->SetCurrentAnimation("jump");
			// Normal movement
			else if (_transform->Velocity.Y != 0.f || _transform->Velocity.X != 0.f)
				_animationComponent->SetCurrentAnimation("walk");
			// No movement
			else
				_animationComponent->SetCurrentAnimation("idle");
		}
	}
};

}

#endif
