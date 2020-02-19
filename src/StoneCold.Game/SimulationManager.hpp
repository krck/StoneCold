
#ifndef STONECOLD_SIMULATIONMANAGER_H
#define STONECOLD_SIMULATIONMANAGER_H

#include "EngineCore.hpp"
#include "ResourceManager.hpp"
#include "PlayerCharacter.hpp"
#include "MapTile.hpp"
#include <iostream>

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

//
// Definitions of what Resources should be loaded
// This includes Player Textures, GUI Fonts, NPC Animations, ...
//
class SimulationManager {
public:
	SimulationManager() : _engine(nullptr), _resourceManager(nullptr) { }
	SimulationManager(const SimulationManager&) = delete;
	SimulationManager& operator=(const SimulationManager&) = delete;

	bool Initialize(EngineCore* engine, ResourceManager* resourceManager);

	//
	// ...
	//
	void LoadGlobalResouces();

	//
	// Load a Level (Map)
	//
	// Create a Map by loading all needed Textures based on LevelType (Grass, Desert, ...)
	// Then those Textures are transformed into MapTiles, based on the MapLayout and finally 
	// pushed to the Engines GameObject List, which will be rendered
	//
	void LoadLevelResouces(LevelType type);

	//
	// ...
	//
	void LoadSequenceResouces();

	~SimulationManager() = default;

private:
	EngineCore* _engine;
	ResourceManager* _resourceManager;
};

}

#endif
