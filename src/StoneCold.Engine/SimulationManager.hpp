
#ifndef STONECOLD_SIMULATIONMANAGER_H
#define STONECOLD_SIMULATIONMANAGER_H

#include "Settings.hpp"
#include "AnimatedSprite.hpp"
#include <vector>

namespace StoneCold::Engine {

typedef std::unique_ptr<Entity>	entity_ptr;

class SimulationManager
{
public:
	SimulationManager(SDL_Renderer* renderer, TextureManager& TextureManager);
	SimulationManager(const SimulationManager&) = delete;
	SimulationManager& operator=(const SimulationManager&) = delete;

	void HandleEvent(const SDL_Event& event);
	void Update(uint timestampOld, uint timestampNew);
	void Render();

private:
	SDL_Renderer* _renderer;
	TextureManager& _textureManager;
	std::unique_ptr<AnimatedSprite> _playerEntity;

};

}

#endif
