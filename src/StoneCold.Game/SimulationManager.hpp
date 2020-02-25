
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
// SimulationManager
//
// One of the StoneCold::Game centrepieces, the SimulationManager
// triggers Resource loading and unloading, creates GameObjects 
// with those Resources and adds/removes them to/from the Engine.
//
// Creating the wohle simulation includes: Loading the GUI and PlayerCharacter, 
// generating Maps, creating Levels from those Maps by adding Tiles and NPCs, etc.
// 
class SimulationManager {
public:
	SimulationManager() : _mapGenerator(MapGenerator()), _engine(nullptr), _resourceManager(nullptr) { }
	SimulationManager(const SimulationManager&) = delete;
	SimulationManager& operator=(const SimulationManager&) = delete;

	bool Initialize(EngineCore* engine, ResourceManager* resourceManager);

	//
	// Clear and (Re-)Load all Global Resources (PlayerCharacter, Fonts, etc.),
	// create the specific GameObjects and feed them to the Engine if needed.
	//
	void LoadGlobalResouces();

	//
	// Clear and (Re-)Load all Level Resources (Map Textures, NPC Textures/Animations), create
	// a new procedurally generated Map and populate that Map with its Tiles and Mobs, etc.
	// Finally add those GameObjects to the Engine, if needed.
	//
	void LoadLevelResouces();

	//
	// Clear and (Re-)Load all Sequence Resources (Cutscene Textures, etc.)
	// ...
	//
	void LoadSequenceResouces();

	~SimulationManager() = default;

private:
	MapGenerator _mapGenerator;
	ResourceManager* _resourceManager;
	EngineCore* _engine;
};

}

#endif
