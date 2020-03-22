
#include "MenuState.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

MenuState::MenuState(uint16 maxEntities, SDL_Renderer* renderer, EngineCore* engine)
	: State(maxEntities, renderer, engine)
	, _camera({ 0.f, 0.f, static_cast<float>(WINDOW_SIZE_WIDTH), static_cast<float>(WINDOW_SIZE_HEIGHT) }) { }


void MenuState::Initialize() {
	// SETUP ECS SYSTEMS

}


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
	// GET RENDER SYSTEM

	//// First: Render the background image
	//_background->Render(_camera);

	//// Last: Render the GUI (always top Layer)
	//for (const auto& gui : _guiObjects)
	//	gui->Render(_camera);
}
