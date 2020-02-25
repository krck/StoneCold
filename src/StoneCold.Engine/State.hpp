
#ifndef STONECOLD_STATE_H
#define STONECOLD_STATE_H

#include "SDL_Base.hpp"
#include "Types.hpp"

namespace StoneCold::Engine {

class State {
public:
	//virtual void Init() = 0;
	//virtual void Cleanup() = 0;

	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void HandleEvent(const uint8* keyStates) = 0;
	virtual void Update(uint frameTime) = 0;
	virtual void Render(SDL_FRect camera) = 0;

	//void ChangeState(CGameEngine* game, CGameState* state) {
	//	game->ChangeState(state);
	//}

protected:
	State() { }
};

}

#endif
