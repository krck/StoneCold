
#include "IntroState.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

IntroState::IntroState(uint16 maxEntities, SDL_Renderer* renderer, EngineCore* engine)
	: State(maxEntities, renderer, engine)
	, _camera({ 0.f, 0.f, static_cast<float>(WINDOW_SIZE_WIDTH), static_cast<float>(WINDOW_SIZE_HEIGHT) }) { }


void IntroState::Initialize() {
	// SETUP ECS SYSTEMS

}


bool IntroState::HandleSDLEvent(const SDL_Event& sdlEvent) {
	// Check if any key was pressed ...
	if (sdlEvent.type == SDL_KEYDOWN) {
		if (_engine->HasState<MenuState>()) {
			auto menuPtr = _engine->GetState<MenuState>();
			_engine->ChangeState(menuPtr);

			return true;
		}
	}

	return false;
}


void IntroState::Render() {
	// GET RENDER SYSTEM

	//// First: Render the background image
	//_background->Render(_camera);

	//// Second: Render any Entity (Moving coulds, etc.)
	//for (const auto& go : _gameObjects)
	//	go->Render(_camera);

	//// Last: Render the GUI (always top Layer)
	//for (const auto& gui : _guiObjects)
	//	gui->Render(_camera);
}
