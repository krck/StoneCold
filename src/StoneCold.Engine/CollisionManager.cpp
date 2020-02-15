
#include "CollisionManager.hpp"

#include <iostream>

using namespace StoneCold::Engine;

void StoneCold::Engine::CollisionManager::UpdateCollisions(std::vector<CollisionComponent*>& collidableObjects) {
    for (auto ccMain : collidableObjects) {
        for (auto ccCheck : collidableObjects) {
            if (ccMain == ccCheck || ccMain->IsFixed && ccCheck->IsFixed)
                continue;

            if (CalculateAABB(ccMain->CollisionDimensions, ccCheck->CollisionDimensions)) {
                ccMain->CollisionWithTag = ccCheck->Tag;
                ccCheck->CollisionWithTag = ccMain->Tag;
                std::cout << ccMain->Tag << " collision with: " << ccCheck->Tag << std::endl;
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
