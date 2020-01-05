
#include "EntityManager.hpp"

using namespace StoneCold;

EntityManager::EntityManager(SDL_Renderer* renderer) : _renderer(renderer) {
	_playerEntity = std::make_unique<Entity>(_renderer, BASE_PATH + "test.png", 90, 81);
}

void EntityManager::HandleEvent(const SDL_Event& event) {
	// Check for KEY_DOWN
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:	_playerEntity->velocity_Y = -1;	break;
		case SDLK_DOWN: _playerEntity->velocity_Y = 1;	break;
		case SDLK_LEFT:	_playerEntity->velocity_X = -1;	break;
		case SDLK_RIGHT: _playerEntity->velocity_X = 1;	break;
		default: break;
		}
	}
	// Check for KEY_UP
	if (event.type == SDL_KEYUP) {
		switch (event.key.keysym.sym) {
		case SDLK_UP:	_playerEntity->velocity_Y = 0;	break;
		case SDLK_DOWN: _playerEntity->velocity_Y = 0;	break;
		case SDLK_LEFT:	_playerEntity->velocity_X = 0;	break;
		case SDLK_RIGHT: _playerEntity->velocity_X = 0;	break;
		default:
			break;
		}
	}
}

void EntityManager::Update() {
	_playerEntity->Update();
}

void EntityManager::Render() {
	// Clear the Frame (white)
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);

	_playerEntity->Render();

	// Render to the Window
	SDL_RenderPresent(_renderer);
}
