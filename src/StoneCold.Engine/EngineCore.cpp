
#include "EngineCore.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

EngineCore::EngineCore()
	: _sdlManager(SDLManager()), _collisionManager(CollisionManager()), _renderer(nullptr)
	, _gameObjects(std::vector<std::unique_ptr<GameObject>>()), _collidableObjects(std::vector<CollisionComponent*>()) { };

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
	// Update/Move all objects
	for (auto& go : _gameObjects)
		go->Update(frameTime);

	// Now check for possible collisions
	_collisionManager.UpdateCollisions(_collidableObjects);
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
	// Add to the main GameObjects list
	_gameObjects.push_back(std::move(gameObject));

	// Check for CollisionComponent and store ptr
	auto go = _gameObjects.back().get();
	if (go->HasComponent<CollisionComponent>())
		_collidableObjects.push_back(go->GetComponent<CollisionComponent>());
}
