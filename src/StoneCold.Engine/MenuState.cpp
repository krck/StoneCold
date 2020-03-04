
#include "MenuState.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

MenuState::MenuState(EngineCore* engine)
	: State(engine)
	, _camera({ 0.f, 0.f, static_cast<float>(WINDOW_SIZE_WIDTH), static_cast<float>(WINDOW_SIZE_HEIGHT) })
	, _background(nullptr)
	, _guiObjects(std::vector<std::unique_ptr<Entity>>()) { }


void MenuState::HandleInputEvent(const std::vector<uint8>& keyStates) {
	// Check if any key was pressed ...
	// Up/Down to select the Buttons
	// Enter to confirm,
	// Backspace to go back (to the Intro)
}


void MenuState::Render() {
	// First: Render the background image
	_background->Render(_camera);

	// Second: Render any Entity (Moving coulds, etc.)
	for (const auto& go : _gameObjects)
		go->Render(_camera);

	// Last: Render the GUI (always top Layer)
	for (const auto& gui : _guiObjects)
		gui->Render(_camera);
}


void MenuState::SetBackground(std::unique_ptr<Entity>&& backgroundObject) {
	// Specific "Add" for the Background Entity
	_background = std::move(backgroundObject);
}


void MenuState::SetGameObjects(std::vector<std::unique_ptr<Entity>>&& gameObjects) {
	// Refresh all Game Objects
	_gameObjects.clear();
	_gameObjects = std::move(gameObjects);
}


void MenuState::SetGUI(std::vector<std::unique_ptr<Entity>>&& guiObjects) {
	// Refresh all GUI Objects
	_guiObjects.clear();
	_guiObjects = std::move(guiObjects);
}
