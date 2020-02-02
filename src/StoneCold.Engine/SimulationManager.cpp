
#include "SimulationManager.hpp"

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

auto animIdle = Animation("idle", {
		{ 0, 0, 26, 20 },
		{ 26, 0, 26, 20 },
		{ 52, 0, 26, 20 },
		{ 78, 0, 26, 20 },
		{ 104, 0, 26, 20 }
	});

auto animWalk = Animation("walk", {
		{ 0, 0, 27, 21 },
		{ 27, 0, 27, 21 },
		{ 54, 0, 27, 21 },
		{ 81, 0, 27, 21 },
		{ 108, 0, 27, 21 },
		{ 135, 0, 27, 21 },
		{ 162, 0, 27, 21 },
		{ 189, 0, 27, 21 }
	});


SimulationManager::SimulationManager(SDL_Renderer* renderer, TextureManager& textureManager) : _renderer(renderer), _textureManager(textureManager) {

	//std

	auto tex = _textureManager.LoadTexture(_renderer, ASSET_PATH + "walk.png");

	// Player sprites are usually 26x20 but they will be rendered 3 times the size 78x60
	_playerEntity = std::make_unique<AnimatedSprite>(_renderer, &animWalk, tex.get(), 78, 60, 100);

}

void SimulationManager::HandleEvent(const SDL_Event& event) {
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

void SimulationManager::Update(uint timestampOld, uint timestampNew) {
	_playerEntity->Update(timestampOld, timestampNew);
}

void SimulationManager::Render() {
	// Clear the Frame (white)
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);

	_playerEntity->Render();

	// Render to the Window
	SDL_RenderPresent(_renderer);
}
