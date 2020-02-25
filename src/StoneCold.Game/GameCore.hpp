
#ifndef STONECOLD_GAMECORE_H
#define STONECOLD_GAMECORE_H

#include "Settings.hpp"
#include "EngineCore.hpp"
#include "ResourceManager.hpp"
#include "SimulationManager.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

//
// This is the central Game class running the main-loop
//
class GameCore {
public:
	GameCore() : _engine(EngineCore()), _resources(ResourceManager()), _simulationManager(SimulationManager()) { };
	GameCore(const GameCore&) = delete;
	GameCore& operator=(const GameCore&) = delete;

	bool Initialize();
	int Run();

	~GameCore() = default;

private:
	EngineCore _engine;
	ResourceManager _resources;
	SimulationManager _simulationManager;
};

}

#endif
