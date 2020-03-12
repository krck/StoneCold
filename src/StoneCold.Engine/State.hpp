
#ifndef STONECOLD_STATE_H
#define STONECOLD_STATE_H

#include "SDL_Base.hpp"
#include "Types.hpp"
#include <vector>

namespace StoneCold::Engine {

using namespace StoneCold::Base;

class EngineCore;

//
// State Interface
//
// There are more elegant ways of creating a Game-State-System, but here the State needs the 
// Engine (which is basically the StateManager) and the Engine needs the State ... obviously. 
//
// But this way State creation and destruction can be in one central
// place. Otherwise States have to create and cleanup each other.
//
class State {
public:
	State(EngineCore* engine) : _engine(engine) { }

	virtual void Init() { } // = 0;
	virtual void Cleanup() { } // = 0;

	virtual void Pause() { } // = 0;
	virtual void Resume() { } // = 0;

	virtual bool HandleSDLEvent(const SDL_Event& sdlEvent) = 0;
	virtual void HandleInputEvent(const std::vector<uint8>& keyStates) = 0;
	virtual void Update(uint32 frameTime) = 0;
	virtual void Render() = 0;

protected:
	EngineCore* _engine;
};

}

#endif