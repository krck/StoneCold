
#include "CollisionManager.hpp"

#include <iostream>

using namespace StoneCold::Engine;

void StoneCold::Engine::CollisionManager::UpdateCollisions(std::vector<GameObject*>& collidableObjects) {
    CollisionComponent* ccMain = nullptr;
    CollisionComponent* ccCheck = nullptr;
    bool result = false;

    for (auto coMain : collidableObjects) {
        for (auto coCheck : collidableObjects) {
            if (coMain == coCheck || (coMain->HasComponent<SpriteComponentFixed>() && coCheck->HasComponent<SpriteComponentFixed>()))
                continue;

            ccMain = coMain->GetComponent<CollisionComponent>();
            ccCheck = coCheck->GetComponent<CollisionComponent>();
            result = CalculateAABB(ccMain->CollisionDimensions, ccCheck->CollisionDimensions);

            if (result) {
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
