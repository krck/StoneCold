
#ifndef STONECOLD_GAMECORE_H
#define STONECOLD_GAMECORE_H

#include "Settings.hpp"
#include "SDLManager.hpp"
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
	GameCore();
	GameCore(const GameCore&) = delete;
	GameCore& operator=(const GameCore&) = delete;

	bool Initialize(const std::string& windowName);
	int Run();

	~GameCore() = default;

private:
	SDLManager _sdl;
	EngineCore _engine;
	ResourceManager _resources;
	SimulationManager _simulation;
};

}

#endif
