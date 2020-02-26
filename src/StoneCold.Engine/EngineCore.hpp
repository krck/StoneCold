
#ifndef STONECOLD_ENGINECORE_H
#define STONECOLD_ENGINECORE_H

#include "Exception.hpp"
#include "SDL_Base.hpp"
#include "Types.hpp"
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <memory>
#include <stack>

namespace StoneCold::Engine {

class EngineCore;

//
// State Interface
//
// Definition has to be here, because the State needs the Engine and the Engine needs the State. There are 
// more elegant ways of creating a State-System, but this way State creation and destruction can be in one
// place (The StoneCold::Game::SimulationManager). Otherwise States have to create and cleanup each other.
//
class State {
public:
	State(EngineCore* engine) : _engine(engine) { }

	virtual void Init() { } // = 0;
	virtual void Cleanup() { } // = 0;
	virtual void Pause() { } // = 0;
	virtual void Resume() { } // = 0;

	virtual void HandleEvent(const uint8* keyStates) = 0;
	virtual void Update(uint frameTime) = 0;
	virtual void Render() = 0;

protected:
	EngineCore* _engine;
};

//
// EngineCore
//
// Directly called from the games main-loop this holds and manages all GameStates,
// distributes SDL_Events and Update calls and SDL_RenderPresent's to the screen
//
class EngineCore {
public:
	EngineCore();
	EngineCore(const EngineCore&) = delete;
	EngineCore& operator=(const EngineCore&) = delete;

	bool Initialize(SDL_Renderer* renderer);
	void HandleEvent(const uint8* keyStates);
	void Update(uint frameTime);
	void Render();

	void ChangeState(State* state);
	void PushState(State* state);
	void PopState();

	//
	// Add a new State to the GameObject based on the State Type
	// Each GameObject can have any State but only one active instance of each Type
	// (type_index is a wrapper class around a std::type_info object, that can be used as index)
	//
	template<typename T>
	void AddState(std::shared_ptr<State>&& state) { _states[std::type_index(typeid(T))] = std::move(state); }

	template<typename T>
	T* GetState() { return static_cast<T*>(_states[std::type_index(typeid(T))].get()); }

	template<typename T>
	bool HasState() const { return (_states.find(std::type_index(typeid(T))) != _states.end()); }

	template<typename T>
	void ClearState() {
		auto state = std::type_index(typeid(T));
		if (_states.find(state) != _states.end()) {
			_states.erase(state);
		}
	}

	~EngineCore() = default;

private:
	SDL_Renderer* _renderer;

	//
	// State Management (as part of the core Engine)
	// Top is the active state that should be updated and rendered
	//
	std::stack<State*> _stateStack;
	std::unordered_map<std::type_index, std::shared_ptr<State>> _states;

};

}

#endif
