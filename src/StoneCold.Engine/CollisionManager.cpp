
#include "CollisionManager.hpp"

using namespace StoneCold::Engine;

void StoneCold::Engine::CollisionManager::UpdateCollisions(std::vector<CollisionComponent*>& collidableObjects) {
	// Check all GameObjects with CollisionComponents against each other
	for (auto ccMain : collidableObjects) {
		ccMain->CollisionWith = nullptr;
		for (auto ccCheck : collidableObjects) {
			// Update the CollisionWith ptr, in case both objects had a collision (two fixed object will never)
			if (ccMain != ccCheck && !(ccMain->IsFixed && ccCheck->IsFixed)
				&& CalculateAABB(ccMain->Hitbox, ccCheck->Hitbox)) {
				ccMain->CollisionWith = ccCheck;
			}
		}
	}
}

bool CollisionManager::CalculateAABB(const SDL_FRect& recA, const SDL_FRect& recB) const {
	// Check the Axis-Aligned Bounding Boxes for overlap
	// Aka. AABB collision. Aka. simplest you can get
	return (recA.x + recA.w >= recB.x
		&& recB.x + recB.w >= recA.x
		&& recA.y + recA.h >= recB.y
		&& recB.y + recB.h >= recA.y);
}
