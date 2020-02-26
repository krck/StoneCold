
#include "GameState.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

GameState::GameState(EngineCore* engine)
	: State(engine)
	, _collisionManager(CollisionManager())
	, _mapObjects(std::unordered_map<hash64, std::vector<std::shared_ptr<GameObject>>>())
	, _gameObjects(std::unordered_map<hash64, std::vector<std::shared_ptr<GameObject>>>())
	, _guiObjects(std::vector<std::shared_ptr<GameObject>>())
	, _collidableObjects(std::vector<CollisionComponent*>())
	, _player(nullptr), _playerTransformation(nullptr)
	, _camera({ 0.f, 0.f, (float)WINDOW_SIZE_WIDTH, (float)WINDOW_SIZE_HEIGHT }) { }

void GameState::HandleEvent(const uint8* keyStates) {
	// Only GameObject that handles input
	_player->HandleEvent(keyStates);

	//for (auto& go : _gameObjects)
	//	go->HandleEvent(keyStates);
}

void GameState::Update(uint frameTime) {
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

void GameState::Render() {
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
}

void GameState::SetPlayer(std::unique_ptr<GameObject>&& gameObject) {
	// Specific "Add" for the Player GameObject
	_player = std::move(gameObject);
	_collidableObjects.push_back(_player->GetComponent<CollisionComponent>());
	_playerTransformation = _player->GetComponent<TransformComponent>();
}

void GameState::SetLevel(std::vector<std::shared_ptr<GameObject>>&& mapObjects, std::vector<std::shared_ptr<GameObject>>&& gameObjects, Vec2i spawnPoint) {
	// Reset all MapTiles, NPCs, Objects, ... and CollisionComponents
	_mapObjects = std::unordered_map<hash64, std::vector<std::shared_ptr<GameObject>>>();
	_gameObjects = std::unordered_map<hash64, std::vector<std::shared_ptr<GameObject>>>();
	_collidableObjects = std::vector<CollisionComponent*>();

	// Add the Levels MapObjects
	for (auto mo : mapObjects) {
		// Check if the MapTile has a CollisionComponent and add it to the colliders
		if (mo->HasComponent<CollisionComponent>())
			_collidableObjects.push_back(mo->GetComponent<CollisionComponent>());

		// Get the MapTiles TextureId and add it to the _mapObjects, grouped by Texture
		hash64 textureId = 1;
		if (_mapObjects.find(textureId) == _mapObjects.end() || _mapObjects[textureId].empty()) {
			_mapObjects[textureId] = std::vector<std::shared_ptr<GameObject>>{ std::move(mo) };
		}
		else {
			_mapObjects[textureId].push_back(std::move(mo));
		}
	}

	// Add the Levels other GameObjects
	for (auto go : gameObjects) {
		// Check if the GameObject has a CollisionComponent and add it to the colliders
		if (go->HasComponent<CollisionComponent>())
			_collidableObjects.push_back(go->GetComponent<CollisionComponent>());

		// Get the GameObjects TextureId and add it to the _gameObjects, grouped by Texture
		hash64 textureId = 1;
		if (_gameObjects.find(textureId) == _gameObjects.end() || _gameObjects[textureId].empty()) {
			_gameObjects[textureId] = std::vector<std::shared_ptr<GameObject>>{ std::move(go) };
		}
		else {
			_gameObjects[textureId].push_back(std::move(go));
		}
	}

	// Add the player CollisionComponen again
	_collidableObjects.push_back(_player->GetComponent<CollisionComponent>());
	// Update the players spawn point
	_playerTransformation->Position.X = static_cast<float>(spawnPoint.X);
	_playerTransformation->Position.Y = static_cast<float>(spawnPoint.Y);
}

void GameState::SetGUI(std::vector<std::shared_ptr<GameObject>>&& guiObjects) {
	// Refresh all GUI Objects
	_guiObjects.clear();
	_guiObjects = std::move(guiObjects);
}
