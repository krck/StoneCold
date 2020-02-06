
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

void EngineCore::HandleEvent(const SDL_Event& event) {
	for (auto& go : _gameObjects)
		go->HandleEvent(event);
}

void EngineCore::Update(uint timestampOld, uint timestampNew) {
	for (auto& go : _gameObjects)
		go->Update(timestampOld, timestampNew);
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
