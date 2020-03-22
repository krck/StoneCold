
#ifndef STONECOLD_COLLISIONDETECTIONSYSTEM_H
#define STONECOLD_COLLISIONDETECTIONSYSTEM_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentArray.hpp"

namespace StoneCold::Engine {

//
// Collision System
//
// Detects simple 2d collisions between Entitys (with CollisionComponents) and
// updates the affected CollisionComponents with a ptr to the object that was hit
//
class CollisionDetectionSystem : public System {
public:
	CollisionDetectionSystem(mask componentMask, EntityComponentArray<CollisionComponent>& collisions)
		: System(componentMask), _collisionComponents(collisions) { }

	CollisionDetectionSystem(const CollisionDetectionSystem&) = delete;
	CollisionDetectionSystem& operator=(const CollisionDetectionSystem&) = delete;

	virtual void Update(uint32 frameTime) override {
		for (const auto& entityId : _entities) {
			// Check all Entitys with CollisionComponents against each other
			//ccMain->CollisionWith = nullptr;
			//for (auto ccCheck : collidableObjects) {
			//	// Update the CollisionWith ptr, in case both objects had a collision (two fixed object will never)
			//	if (ccMain != ccCheck && !(ccMain->IsFixed && ccCheck->IsFixed)
			//		&& CalculateAABB(ccMain->CollisionBox, ccCheck->CollisionBox)) {
			//		ccMain->CollisionWith = ccCheck;
			//	}
			//}
		}
	}

private:
	//
	// Check the Axis-Aligned Bounding Boxes for overlap
	// Aka. AABB collision. Aka. simplest you can get
	//
	bool CalculateAABB(const SDL_FRect& recA, const SDL_FRect& recB) const {
		return (recA.x + recA.w >= recB.x
			&& recB.x + recB.w >= recA.x
			&& recA.y + recA.h >= recB.y
			&& recB.y + recB.h >= recA.y);
	}

private:
	EntityComponentArray<CollisionComponent>& _collisionComponents;
};

}

#endif
