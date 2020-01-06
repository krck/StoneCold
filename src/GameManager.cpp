
#include "GameManager.hpp"

using namespace StoneCold;

GameManager::GameManager(SDL_Renderer* renderer, ResourceManager& resourceManager) : _renderer(renderer), _resourceManager(resourceManager) {
	auto tex = _resourceManager.LoadTexture(_renderer, BASE_PATH + "test.png");
	_playerEntity = std::make_unique<Sprite>(_renderer, tex.get(), 90, 81);

}

void GameManager::HandleEvent(const SDL_Event& event) {
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

void GameManager::Update() {
	_playerEntity->Update();
}

void GameManager::Render() {
	// Clear the Frame (white)
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);

	_playerEntity->Render();

	// Render to the Window
	SDL_RenderPresent(_renderer);
}
