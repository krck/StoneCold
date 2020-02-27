
#ifndef STONECOLD_INTROSTATE_H
#define STONECOLD_INTROSTATE_H

#include "Component.hpp"
#include "EngineCore.hpp"
#include "GameState.hpp"
#include <algorithm>

namespace StoneCold::Engine {

class IntroState : public State {
public:
	IntroState(EngineCore* engine);
	IntroState(const IntroState&) = delete;
	IntroState& operator=(const IntroState&) = delete;

	virtual bool HandleSDLEvent(const SDL_Event& sdlEvent) override { return false; }
	virtual void HandleInputEvent(const std::vector<uint8>& keyStates) override;
	virtual void Update(uint frameTime) override { /* Nothing to update. Scene is static */ }
	virtual void Render() override;

	void SetBackground(std::unique_ptr<GameObject>&& backgroundObject);
	void SetGameObjects(std::vector<std::shared_ptr<GameObject>>&& gameObjects);
	void SetGUI(std::vector<std::shared_ptr<GameObject>>&& guiObjects);

	~IntroState() = default;

private:
	SDL_FRect _camera;

	//
	// Pointers to all GameObjects (Background images, GUI objects, ...)
	//
	std::unique_ptr<GameObject> _background;
	std::vector<std::shared_ptr<GameObject>> _gameObjects;
	std::vector<std::shared_ptr<GameObject>> _guiObjects;

};

}

#endif
