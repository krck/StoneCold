
#include "IntroState.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

IntroState::IntroState(EngineCore* engine)
	: State(engine)
	, _camera({ 0.f, 0.f, static_cast<float>(WINDOW_SIZE_WIDTH), static_cast<float>(WINDOW_SIZE_HEIGHT) })
	, _background(nullptr)
	, _guiObjects(std::vector<std::unique_ptr<Entity>>()) { }


void IntroState::HandleInputEvent(const std::vector<uint8>& keyStates) {
	// Check if any key was pressed ...
	if (std::any_of(keyStates.begin(), keyStates.end(), [](uint8 i) {return (i == 1); })) {
		// and switch from Intro to MenuState, if its available
		if (_engine->HasState<MenuState>()) {
			auto gamePtr = _engine->GetState<MenuState>();
			_engine->ChangeState(gamePtr);
		}
	}
}


void IntroState::Render() {
	// First: Render the background image
	_background->Render(_camera);

	// Second: Render any Entity (Moving coulds, etc.)
	for (const auto& go : _gameObjects)
		go->Render(_camera);

	// Last: Render the GUI (always top Layer)
	for (const auto& gui : _guiObjects)
		gui->Render(_camera);
}


void IntroState::SetBackground(std::unique_ptr<Entity>&& backgroundObject) {
	// Specific "Add" for the Background Entity
	_background = std::move(backgroundObject);
}


void IntroState::SetGameObjects(std::vector<std::unique_ptr<Entity>>&& gameObjects) {
	// Refresh all Game Objects
	_gameObjects.clear();
	_gameObjects = std::move(gameObjects);
}


void IntroState::SetGUI(std::vector<std::unique_ptr<Entity>>&& guiObjects) {
	// Refresh all GUI Objects
	_guiObjects.clear();
	_guiObjects = std::move(guiObjects);
}
