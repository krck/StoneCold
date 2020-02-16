
#include "CollisionManager.hpp"

using namespace StoneCold::Engine;

void StoneCold::Engine::CollisionManager::UpdateCollisions(std::vector<CollisionComponent*>& collidableObjects) {
	for (auto ccMain : collidableObjects) {
		ccMain->CollisionWith = nullptr;
		for (auto ccCheck : collidableObjects) {
			if (ccMain != ccCheck && !(ccMain->IsFixed && ccCheck->IsFixed)
				&& CalculateAABB(ccMain->CollisionDimensions, ccCheck->CollisionDimensions)) {
				ccMain->CollisionWith = ccCheck;
			}
		}
	}
}

bool CollisionManager::CalculateAABB(const SDL_FRect& recA, const SDL_FRect& recB) const {
	return (recA.x + recA.w >= recB.x
		&& recB.x + recB.w >= recA.x
		&& recA.y + recA.h >= recB.y
		&& recB.y + recB.h >= recA.y);
}
