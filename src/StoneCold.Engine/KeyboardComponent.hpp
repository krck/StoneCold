
#ifndef STONECOLD_KEYBOARDCOMPONENT_H
#define STONECOLD_KEYBOARDCOMPONENT_H

#include "SDL_Base.hpp"
#include "Component.hpp"
#include "TransformComponent.hpp"

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
	KeyboardComponent() = default;

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
		// Get the TransformComponent to write transformations based on the Keyboard input
		_transform = _gameObject->GetComponent<TransformComponent>();
	}

	void HandleEvent(const SDL_Event& event) override {
		if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym) {
			case SDLK_UP: _transform->Velocity.Y = -1; break;
			case SDLK_DOWN: _transform->Velocity.Y = 1; break;
			case SDLK_LEFT: _transform->Velocity.X = -1; break;
			case SDLK_RIGHT: _transform->Velocity.X = 1; break;
			default: break;
			}
		}
		// Why not else if ? Test
		if (event.type == SDL_KEYUP) {
			switch (event.key.keysym.sym) {
			case SDLK_UP: _transform->Velocity.Y = 0; break;
			case SDLK_DOWN: _transform->Velocity.Y = 0; break;
			case SDLK_LEFT: _transform->Velocity.X = 0; break;
			case SDLK_RIGHT: _transform->Velocity.X = 0; break;
			default: break;
			}
		}
	}
};

}

#endif
