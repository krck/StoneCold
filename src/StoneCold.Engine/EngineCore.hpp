
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
	void AddNewGameObject(std::unique_ptr<GameObject>&& gameObject);

	std::vector<std::vector<MapTileTypes>>* GetNewMap();

	~EngineCore() = default;

private:
	SDLManager _sdlManager;
	CollisionManager _collisionManager;
	MapGenerator _mapGenerator;
	SDL_Renderer* _renderer;
	SDL_FRect _camera;
	
	//
	// Pointers to the Player GameObject for fast access
	//
	std::unique_ptr<GameObject> _player;
	TransformComponent* _playerTransformation;

	//
	// Vector with all GameObjects (Player, NPCs, MapTiles, ...)
	// that need to be updated and rendered in every loop iteration
	//
	// Group (and render) this by SDL_Texture for better performance
	//
	std::vector<std::unique_ptr<GameObject>> _gameObjects;

	//
	// Based on vector _gameObjects, this stores a pointer
	// to each GameObject, that has a CollisionComponent
	//
	std::vector<CollisionComponent*> _collidableObjects;
};

}

#endif
