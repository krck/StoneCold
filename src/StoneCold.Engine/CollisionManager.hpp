
#ifndef STONECOLD_COLLISIONMANAGER_H
#define STONECOLD_COLLISIONMANAGER_H

#include "SDL_Base.hpp"
#include "CollisionComponent.hpp"
#include "SpriteComponentFixed.hpp"

namespace StoneCold::Engine {

class CollisionManager {
public:
	CollisionManager() { }
	CollisionManager(const CollisionManager&) = delete;
	CollisionManager& operator=(const CollisionManager&) = delete;

	void UpdateCollisions(std::vector<CollisionComponent*>& collidableObjects);

	~CollisionManager() = default;

private:
	bool CalculateAABB(const SDL_FRect& recA, const SDL_FRect& recB) const;


};

}

#endif
