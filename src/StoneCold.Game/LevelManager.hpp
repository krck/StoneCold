
#ifndef STONECOLD_LEVELMANAGER_H
#define STONECOLD_LEVELMANAGER_H

#include "GameResources.hpp"
#include "EngineCore.hpp"
#include "MapTile.hpp"
#include <vector>

namespace StoneCold::Game {

class LevelManager {
public:
	LevelManager() : _resourceManager(nullptr), _gameResources(nullptr) { }
	LevelManager(const LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;

	bool Initialize(ResourceManager* resourceManager, GameResources* gameResources);

	//
	// Load a Level (Map)
	//
	// Create a Map by loading all needed Textures based on LevelType (Grass, Desert, ...)
	// Then those Textures are transformed into MapTiles, based on the MapLayout and finally 
	// pushed to the Engines GameObject List, which will be rendered
	//
	void LoadLevel(EngineCore* engine, LevelType type);

	~LevelManager() = default;

private:
	ResourceManager* _resourceManager;
	GameResources* _gameResources;
};

}

#endif
