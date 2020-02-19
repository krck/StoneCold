
#include "EngineCore.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

EngineCore::EngineCore()
	: _sdlManager(SDLManager()), _collisionManager(CollisionManager()), _mapGenerator(MapGenerator()), _renderer(nullptr)
	, _gameObjects(std::vector<std::unique_ptr<GameObject>>()), _collidableObjects(std::vector<CollisionComponent*>())
	, _camera({ 0.f, 0.f, (float)WINDOW_SIZE_WIDTH, (float)WINDOW_SIZE_HEIGHT }), _player(nullptr) { };

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
	// Only GameObject that handles input
	_player->HandleEvent(keyStates);

	//for (auto& go : _gameObjects)
	//	go->HandleEvent(keyStates);
}

void EngineCore::Update(uint frameTime) {
	// Now check for possible collisions
	_collisionManager.UpdateCollisions(_collidableObjects);

	// Update/Move all objects
	_player->Update(frameTime);
	for (auto& go : _gameObjects)
		go->Update(frameTime);

	// Center the camera over the Player
	_camera.x = _playerTransformation->Position.X - (WINDOW_SIZE_WIDTH / 2.f);
	_camera.y = _playerTransformation->Position.Y - (WINDOW_SIZE_HEIGHT / 2.f);

	// Keep the camera in bounds
	//if (_camera.x < 0) _camera.x = 0;
	//if (_camera.y < 0) _camera.y = 0;
	//if (_camera.x > _camera.w) _camera.x = _camera.w;
	//if (_camera.y > _camera.h) _camera.y = _camera.h;
}

void EngineCore::Render() {
	// Clear the Frame (white)
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);

	// Render any GameObject (Map, NPC, ...) first
	for (auto& go : _gameObjects) 
		go->Render(_camera);

	// Render the Player second
	_player->Render(_camera);

	// Render the GUI last (always top Layer)

	// Swap render buffer to the Window
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

void StoneCold::Engine::EngineCore::AddPlayer(std::unique_ptr<GameObject>&& gameObject) {
	// Specific "Add" for the Player GameObject
	_player = std::move(gameObject);
	_collidableObjects.push_back(_player->GetComponent<CollisionComponent>());
	_playerTransformation = _player->GetComponent<TransformComponent>();
}

const std::vector<std::vector<MapTileTypes>>& StoneCold::Engine::EngineCore::GetNewMap() {
	return _mapGenerator.GenerateMap(Vec2i(50, 50));
}