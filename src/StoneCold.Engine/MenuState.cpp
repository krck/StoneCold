
#include "MenuState.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

MenuState::MenuState(EngineCore* engine)
	: State(engine)
	, _camera({ 0.f, 0.f, static_cast<float>(WINDOW_SIZE_WIDTH), static_cast<float>(WINDOW_SIZE_HEIGHT) })
	, _background(nullptr)
	, _guiObjects(std::vector<std::unique_ptr<Entity>>()) { }


bool MenuState::HandleSDLEvent(const SDL_Event& sdlEvent) {
	// Up/Down to select the Buttons
	// Enter to confirm,
	// Backspace to go back (to the Intro)

	// Check if any key was pressed ...
	if (sdlEvent.type == SDL_KEYDOWN) {
		if (_engine->HasState<GameState>()) {
			auto gamePtr = _engine->GetState<GameState>();
			_engine->ChangeState(gamePtr);

			return true;
		}
	}

	return false;
}


void MenuState::Render() {
	// First: Render the background image
	_background->Render(_camera);

	// Last: Render the GUI (always top Layer)
	for (const auto& gui : _guiObjects)
		gui->Render(_camera);
}


void MenuState::SetBackground(std::unique_ptr<Entity>&& backgroundObject) {
	// Specific "Add" for the Background Entity
	_background = std::move(backgroundObject);
}


void MenuState::SetButton(std::unique_ptr<Entity>&& buttonObject) {

}


void MenuState::SetGUI(std::vector<std::unique_ptr<Entity>>&& guiObjects) {
	// Refresh all GUI Objects
	_guiObjects.clear();
	_guiObjects = std::move(guiObjects);
}
