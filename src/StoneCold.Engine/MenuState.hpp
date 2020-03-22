
#ifndef STONECOLD_MENUSTATE_H
#define STONECOLD_MENUSTATE_H

#include "Entity.hpp"
#include "EngineCore.hpp"
#include "GameState.hpp"
#include <algorithm>

namespace StoneCold::Engine {

class MenuState : public State {
public:
	MenuState(uint16 maxEntities, SDL_Renderer* renderer, EngineCore* engine);
	MenuState(const MenuState&) = delete;
	MenuState& operator=(const MenuState&) = delete;

	virtual void Initialize() override;

	virtual bool HandleSDLEvent(const SDL_Event& sdlEvent) override;
	virtual void HandleInputEvent(const std::vector<uint8>& keyStates) override { }
	virtual void Update(uint32 frameTime) override { /* Nothing to update. Scene is static */ }
	virtual void Render() override;

	~MenuState() = default;

private:
	SDL_FRect _camera;

};

}

#endif
