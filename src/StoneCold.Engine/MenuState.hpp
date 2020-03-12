
#ifndef STONECOLD_MENUSTATE_H
#define STONECOLD_MENUSTATE_H

#include "Component.hpp"
#include "EngineCore.hpp"
#include "GameState.hpp"
#include <algorithm>

namespace StoneCold::Engine {

class MenuState : public State {
public:
	MenuState(EngineCore* engine);
	MenuState(const MenuState&) = delete;
	MenuState& operator=(const MenuState&) = delete;

	virtual bool HandleSDLEvent(const SDL_Event& sdlEvent) override;
	virtual void HandleInputEvent(const std::vector<uint8>& keyStates) override { }
	virtual void Update(uint32 frameTime) override { /* Nothing to update. Scene is static */ }
	virtual void Render() override;

	void SetBackground(std::unique_ptr<Entity>&& backgroundObject);
	void SetButton(std::unique_ptr<Entity>&& buttonObject);
	void SetGUI(std::vector<std::unique_ptr<Entity>>&& guiObjects);

	~MenuState() = default;

private:
	SDL_FRect _camera;

	//
	// Pointers to all Entitys (Background images, GUI objects, ...)
	//
	std::unique_ptr<Entity> _background;
	std::vector<std::unique_ptr<Entity>> _guiObjects;

};

}

#endif
