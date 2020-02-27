
#ifndef STONECOLD_MENUSTATE_H
#define STONECOLD_MENUSTATE_H

#include "EngineCore.hpp"

namespace StoneCold::Engine {

class MenuState : public State {
public:
	MenuState(EngineCore* engine) : State(engine) { }

	virtual bool HandleSDLEvent(const SDL_Event& sdlEvent) override { return false; }
	virtual void HandleInputEvent(const std::vector<uint8>& keyStates) override;
	virtual void Update(uint frameTime) override;
	virtual void Render() override;
};

}

#endif
