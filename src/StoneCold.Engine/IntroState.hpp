
#ifndef STONECOLD_INTROSTATE_H
#define STONECOLD_INTROSTATE_H

#include "EngineCore.hpp"

namespace StoneCold::Engine {

class IntroState : public State {
public:
	IntroState(EngineCore* engine) : State(engine) { }

	virtual void HandleEvent(const uint8* keyStates) override;
	virtual void Update(uint frameTime) override;
	virtual void Render() override;
};

}

#endif
