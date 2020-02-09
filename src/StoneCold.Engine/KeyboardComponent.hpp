
#ifndef STONECOLD_KEYBOARDCOMPONENT_H
#define STONECOLD_KEYBOARDCOMPONENT_H

#include "SDL_Base.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"

#include <iostream>
#include <string>

namespace StoneCold::Engine {

//
// Keyboard (Input) Controller
// Dependent on: TransformComponent
//
// Contains logic to process any Keyboard input based on SDL_Events
// Needs a GameObject with a TransformComponent to store the updates
// 
class KeyboardComponent : public IComponent {
private:
	TransformComponent* _transform;

public:
	KeyboardComponent() : _transform(nullptr) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
		// Get the TransformComponent to write transformations based on the Keyboard input
		_transform = _gameObject->GetComponent<TransformComponent>();
	}

	void HandleEvent(const uint8* keyStates) override {
		// For each keykeyStates contains a value of 1 if pressed and a value of 0 if not pressed
		// Add negative and positive velocity so the sprite doesn't move if both are pressed at the same time
		_transform->Velocity.Y = (-1.0f * keyStates[SDL_SCANCODE_UP]) + keyStates[SDL_SCANCODE_DOWN];
		_transform->Velocity.X = (-1.0f * keyStates[SDL_SCANCODE_LEFT]) + keyStates[SDL_SCANCODE_RIGHT];

		if (keyStates[SDL_SCANCODE_SPACE]) {
			// y -1 x 1		true
			// y -1 x -1	false
			// y 1  x -1	false
			// y 1	x 1		false
			_transform->Velocity.Y *= 3.0f;
			_transform->Velocity.X *= 3.0f;
		}
	}
};

}

#endif
