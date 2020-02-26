
#include "EngineCore.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

EngineCore::EngineCore()
	: _renderer(nullptr)
	, _stateStack(std::stack<State*>())
	, _states(std::unordered_map<std::type_index, std::shared_ptr<State>>()) { };

bool EngineCore::Initialize(SDL_Renderer* renderer) {
	if (renderer != nullptr) {
		_renderer = renderer;
		return true;
	}
	else {
		return false;
	}
}

void EngineCore::HandleEvent(const uint8* keyStates) {
	// Pass Keyboard Events to the current State / Scene
	_stateStack.top()->HandleEvent(keyStates);
}

void EngineCore::Update(uint frameTime) {
	// Update the current State / Scene
	_stateStack.top()->Update(frameTime);
}

void EngineCore::Render() {
	// Clear the Frame (white)
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);

	// Render the current State / Scene
	_stateStack.top()->Render();

	// Swap render buffer to the Window
	SDL_RenderPresent(_renderer);
}

void EngineCore::ChangeState(State* state) {
	// Cleanup the current state
	if (!_stateStack.empty()) {
		_stateStack.top()->Cleanup();
		_stateStack.pop();
	}

	// Store and init the new state
	_stateStack.push(state);
	_stateStack.top()->Init();
}

void EngineCore::PushState(State* state) {
	// Pause current state
	if (!_stateStack.empty()) {
		_stateStack.top()->Pause();
	}

	// Store and init the new state
	_stateStack.push(state);
	_stateStack.top()->Init();
}

void EngineCore::PopState() {
	// Cleanup the current state
	if (!_stateStack.empty()) {
		_stateStack.top()->Cleanup();
		_stateStack.pop();
	}

	// Resume previous state
	if (!_stateStack.empty()) {
		_stateStack.top()->Resume();
	}
}
