
#include "EngineCore.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

EngineCore::EngineCore()
	: _sdlManager(SDLManager()), _collisionManager(CollisionManager()), _renderer(nullptr)
	, _mapObjects(std::unordered_map<hash64, std::vector<std::shared_ptr<GameObject>>>())
	, _gameObjects(std::unordered_map<hash64, std::vector<std::shared_ptr<GameObject>>>())
	, _guiObjects(std::vector<std::shared_ptr<GameObject>>())
	, _collidableObjects(std::vector<CollisionComponent*>())
	, _player(nullptr), _playerTransformation(nullptr)
	, _camera({ 0.f, 0.f, (float)WINDOW_SIZE_WIDTH, (float)WINDOW_SIZE_HEIGHT }) { };

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
	for (const auto& gameOs : _gameObjects)
		for (const auto& go : gameOs.second)
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

	// First: Render any MapTile batched by Texture hash
	for (const auto& mapOs : _mapObjects)
		for (const auto& mo : mapOs.second)
			mo->Render(_camera);

	// Second: Render any GameObject (NPC, ...) batched by Texture hash
	for (const auto& gameOs : _gameObjects)
		for (const auto& go : gameOs.second)
			go->Render(_camera);

	// Third: Render the Player
	_player->Render(_camera);

	// Last: Render the GUI (always top Layer)
	for (const auto& gui : _guiObjects)
		gui->Render(_camera);

	// Swap render buffer to the Window
	SDL_RenderPresent(_renderer);
}

void StoneCold::Engine::EngineCore::AddPlayer(std::unique_ptr<GameObject>&& gameObject) {
	// Specific "Add" for the Player GameObject
	_player = std::move(gameObject);
	_collidableObjects.push_back(_player->GetComponent<CollisionComponent>());
	_playerTransformation = _player->GetComponent<TransformComponent>();
}

void StoneCold::Engine::EngineCore::AddNewMapObject(hash64 textureId, std::shared_ptr<GameObject>&& mapObject) {
	// Check for CollisionComponent and store ptr
	if (mapObject->HasComponent<CollisionComponent>())
		_collidableObjects.push_back(mapObject->GetComponent<CollisionComponent>());

	// Add a new vector in case no hash exists
	if (_mapObjects.find(textureId) == _mapObjects.end() || _mapObjects[textureId].empty()) {
		_mapObjects[textureId] = std::vector<std::shared_ptr<GameObject>>{ std::move(mapObject) };
	}
	else {
		_mapObjects[textureId].push_back(std::move(mapObject));
	}
}

void StoneCold::Engine::EngineCore::AddNewGameObject(hash64 textureId, std::shared_ptr<GameObject>&& gameObject) {
	// Check for CollisionComponent and store ptr
	if (gameObject->HasComponent<CollisionComponent>())
		_collidableObjects.push_back(gameObject->GetComponent<CollisionComponent>());

	// Add a new vector in case no hash exists
	if (_gameObjects.find(textureId) == _gameObjects.end() || _gameObjects[textureId].empty()) {
		_gameObjects[textureId] = std::vector<std::shared_ptr<GameObject>>{ std::move(gameObject) };
	}
	else {
		_gameObjects[textureId].push_back(std::move(gameObject));
	}
}

void StoneCold::Engine::EngineCore::AddNewGuiObject(hash64 textureId, std::shared_ptr<GameObject>&& guiObject) {
	// Add a new vector in case no hash exists
	_guiObjects.push_back(std::move(guiObject));
}

void StoneCold::Engine::EngineCore::UnloadGameObjects(ResourceLifeTime resourceLifeTime) {
	if (resourceLifeTime == ResourceLifeTime::Global) {
		// Do nothing for now.
	}
	else if (resourceLifeTime == ResourceLifeTime::Level) {
		_mapObjects = std::unordered_map<hash64, std::vector<std::shared_ptr<GameObject>>>();
		_gameObjects = std::unordered_map<hash64, std::vector<std::shared_ptr<GameObject>>>();
		_guiObjects = std::vector<std::shared_ptr<GameObject>>();
		_collidableObjects = std::vector<CollisionComponent*>();
		// Add the player CollisionComponen again (has Global LifeTime)
		_collidableObjects.push_back(_player->GetComponent<CollisionComponent>());
	}
	else if (resourceLifeTime == ResourceLifeTime::Sequence) {
		// Do nothing for now.
	}
}

void StoneCold::Engine::EngineCore::SetPlayerPosition(Vec2 position) {
	_playerTransformation->Position.X = position.X;
	_playerTransformation->Position.Y = position.Y;
}
