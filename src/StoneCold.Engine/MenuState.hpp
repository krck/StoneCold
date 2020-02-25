
#ifndef STONECOLD_MENUSTATE_H
#define STONECOLD_MENUSTATE_H

#include "State.hpp"

namespace StoneCold::Engine {

class MenuState : public State {
public:
	virtual void Pause() override;
	virtual void Resume() override;
	virtual void HandleEvent(const uint8* keyStates) override;
	virtual void Update(uint frameTime) override;
	virtual void Render(SDL_FRect camera) override;
};

}

#endif
