
#ifndef STONECOLD_ENTITYMANAGER_H
#define STONECOLD_ENTITYMANAGER_H

#include "Entity.hpp"
#include <vector>

namespace StoneCold {

typedef std::unique_ptr<Entity>		entity_ptr;

class EntityManager
{
public:
	EntityManager(SDL_Renderer* renderer);

	void AddEntity();

	void HandleEvent(const SDL_Event& event);
	void Update();
	void Render();

private:
	SDL_Renderer* _renderer;
	entity_ptr _playerEntity;
	std::vector<entity_ptr> _mapEntities;

};

}

#endif
