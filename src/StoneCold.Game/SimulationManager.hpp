
#ifndef STONECOLD_SIMULATIONMANAGER_H
#define STONECOLD_SIMULATIONMANAGER_H

#include "EngineCore.hpp"
#include "MapManager.hpp"
#include "IntroState.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include "ResourceManager.hpp"
#include "Background.hpp"
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
// from those Resources and adds/removes them to/from (Game) States.
//
// Creating the wohle simulation includes: Loading the GUI and PlayerCharacter, 
// generating Maps, creating Levels from those Maps by adding Tiles and NPCs, etc.
// 
class SimulationManager {
public:
	SimulationManager() : _mapManager(MapManager()), _engine(nullptr), _resourceManager(nullptr), _renderer(nullptr) { }
	SimulationManager(const SimulationManager&) = delete;
	SimulationManager& operator=(const SimulationManager&) = delete;

	bool Initialize(EngineCore* engine, ResourceManager* resourceManager, SDL_Renderer* renderer);

	void CreateIntroState();
	void CreateGameState();
	void CreateMenuState();

	//
	// Clear and (Re-)Load all Game Resources (Map Textures, NPC Textures/Animations),
	// create a new procedurally generated Map and populate that Map with its Tiles 
	// and Mobs, etc. and finally add those GameObjects to the Engine, if needed.
	//
	void LoadLevel();

	~SimulationManager() = default;

private:
	MapManager _mapManager;
	ResourceManager* _resourceManager;
	EngineCore* _engine;
	SDL_Renderer* _renderer;
};

}

#endif
