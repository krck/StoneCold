
#include "MenuState.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

MenuState::MenuState(uint16 maxEntities, SDL_Renderer* renderer, EngineCore* engine)
	: State(maxEntities, renderer, engine)
	, _animationSystem(nullptr)
	, _staticRenderSystem(nullptr)
	, _layeredRenderSystem(nullptr)
	, _camera({ 0.f, 0.f, static_cast<float>(WINDOW_WIDTH), static_cast<float>(WINDOW_HEIGHT) }) { }


void MenuState::Initialize() {
	// Create all Systems needed by the GameState ECS (keep ptr variables for quick access)
	_animationSystem = std::make_shared<AnimationSystem>(_ecs);
	_staticRenderSystem = std::make_shared<StaticRenderSystem>(_renderer, _ecs);
	_layeredRenderSystem = std::make_shared<LayeredRenderSystem>(_renderer, _ecs);

	// Add all the GameState Systems to the ECS
	_ecs.AddSystem<AnimationSystem>(_animationSystem);
	_ecs.AddSystem<StaticRenderSystem>(_staticRenderSystem);
	_ecs.AddSystem<LayeredRenderSystem>(_layeredRenderSystem);
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
	_staticRenderSystem->Render(_camera);
	_layeredRenderSystem->Render(_camera);
}
