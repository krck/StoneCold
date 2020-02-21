
#ifndef STONECOLD_ENGINECORE_H
#define STONECOLD_ENGINECORE_H

#include "SDLManager.hpp"
#include "Exception.hpp"
#include "TransformComponent.hpp"
#include "CollisionManager.hpp"
#include "MapGenerator.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace StoneCold::Engine {

class EngineCore {
public:
	EngineCore();
	EngineCore(const EngineCore&) = delete;
	EngineCore& operator=(const EngineCore&) = delete;

	inline SDL_Renderer* GetSDLRenderer() { return _renderer; }

	bool Initialize(const std::string& windowName);
	void HandleEvent(const uint8* keyStates);
	void Update(uint frameTime);
	void Render();

	void AddPlayer(std::unique_ptr<GameObject>&& gameObject);
	void AddNewMapObject(hash64 textureId, std::shared_ptr<GameObject>&& mapObject);
	void AddNewGameObject(hash64 textureId, std::shared_ptr<GameObject>&& gameObject);
	void AddNewGuiObject(hash64 textureId, std::shared_ptr<GameObject>&& guiObject);

	void UnloadGameObjects(ResourceLifeTime resourceLifeTime);

	void SetPlayerPosition(Vec2 position);

	~EngineCore() = default;

private:
	SDLManager _sdlManager;
	CollisionManager _collisionManager;
	SDL_Renderer* _renderer;
	SDL_FRect _camera;

	//
	// Pointers to the Player GameObject for fast access
	// ResourceLifeTime::Global
	//
	std::unique_ptr<GameObject> _player;
	TransformComponent* _playerTransformation;

	//
	// unordered_maps with all GameObjects (Player, NPCs, MapTiles, ...)
	// Each map has a TextureResource hash as key to batch render by Texture
	//
	// Each map is (indirectly) linked to a ResourceLifeTime
	// _mapObjects:		ResourceLifeTime::Level
	// _gameObjects:	ResourceLifeTime::Level
	// _guiObjects:		ResourceLifeTime::Global
	//
	std::unordered_map<hash64, std::vector<std::shared_ptr<GameObject>>> _mapObjects;
	std::unordered_map<hash64, std::vector<std::shared_ptr<GameObject>>> _gameObjects;
	std::vector<std::shared_ptr<GameObject>> _guiObjects;

	//
	// Based on the GameObject maps, this stores a pointer
	// to each GameObject, that has a CollisionComponent
	//
	// ResourceLifeTime::Level
	//
	std::vector<CollisionComponent*> _collidableObjects;
};

}

#endif
