
#include "EngineCore.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

bool EngineCore::Initialize(const std::string& windowName) {
	// Init SDL will create and show the Application Window
	if (_sdlManager.InitializeSDL(windowName)) {
		_renderer = _sdlManager.GetSDLRenderer();
		return true;
	}
	else {
		return false;
	}
}

void EngineCore::HandleEvent(const uint8* keyStates) {
	for (auto& go : _gameObjects)
		go->HandleEvent(keyStates);
}

void EngineCore::Update(uint frameTime) {
	for (auto& go : _gameObjects)
		go->Update(frameTime);
}

void EngineCore::Render() {
	// Clear the Frame (white)
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);

	for (auto& go : _gameObjects)
		go->Render();

	// Render to the Window
	SDL_RenderPresent(_renderer);
}

void EngineCore::AddNewGameObject(std::unique_ptr<GameObject>&& gameObject) {
	_gameObjects.push_back(std::move(gameObject));
}
