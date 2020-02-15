
#ifndef STONECOLD_MAPMANAGER_H
#define STONECOLD_MAPMANAGER_H

#include "GameResources.hpp"
#include "EngineCore.hpp"
#include "MapTile.hpp"
#include <vector>

namespace StoneCold::Game {

const std::vector<std::vector<int>> tmp_map = {
	{ 1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
};


class MapManager {
public:
	MapManager() : _resourceManager(nullptr), _gameResources(nullptr) { }
	MapManager(const MapManager&) = delete;
	MapManager& operator=(const MapManager&) = delete;

	bool Initialize(ResourceManager* resourceManager, GameResources* gameResources);

	//
	// Load a Map
	//
	// Create a Map by loading all needed Textures based on LevelType (Grass, Desert, ...)
	// Then those Textures are transformed into MapTiles, based on the MapLayout and finally 
	// pushed to the Engines GameObject List, which will be rendered
	//
	void LoadMap(EngineCore* engine, LevelType type, const std::vector<std::vector<int>> mapLayout);

	~MapManager() = default;

private:
	ResourceManager* _resourceManager;
	GameResources* _gameResources;
};

}

#endif
