
#ifndef STONECOLD_GAMEMANAGER_H
#define STONECOLD_GAMEMANAGER_H

#include "ResourceManager.hpp"
#include "Sprite.hpp"
#include <vector>

namespace StoneCold {

typedef std::unique_ptr<Entity>	entity_ptr;

class GameManager
{
public:
	GameManager(SDL_Renderer* renderer, ResourceManager& resourceManager);
	GameManager(const GameManager&) = delete;
	GameManager& operator=(const GameManager&) = delete;

	void HandleEvent(const SDL_Event& event);
	void Update();
	void Render();

private:
	SDL_Renderer* _renderer;
	ResourceManager& _resourceManager;
	std::unique_ptr<Sprite> _playerEntity;

};

}

#endif
