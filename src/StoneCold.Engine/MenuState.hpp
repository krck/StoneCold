
#ifndef STONECOLD_MENUSTATE_H
#define STONECOLD_MENUSTATE_H

#include "EngineCore.hpp"

namespace StoneCold::Engine {

class MenuState : public State {
public:
	MenuState(EngineCore* engine) : State(engine) { }

	virtual void HandleEvent(const uint8* keyStates) override;
	virtual void Update(uint frameTime) override;
	virtual void Render() override;
};

}

#endif
