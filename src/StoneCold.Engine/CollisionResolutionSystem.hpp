
#ifndef STONECOLD_COLLISIONRESOLUTIONSYSTEM_H
#define STONECOLD_COLLISIONRESOLUTIONSYSTEM_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentArray.hpp"

namespace StoneCold::Engine {

class CollisionResolutionSystem : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a Collision and Transformation Component will be updated with this System
	//
	CollisionResolutionSystem(EntityComponentArray<CollisionComponent>& collisions, EntityComponentArray<TransformationComponent>& transf)
		: System((GetComponentMask<CollisionComponent>() | GetComponentMask<TransformationComponent>()))
		, _collisionComponents(collisions), _transformComponents(transf) { }

	CollisionResolutionSystem(const CollisionResolutionSystem&) = delete;
	CollisionResolutionSystem& operator=(const CollisionResolutionSystem&) = delete;

	virtual void Update(uint32 frameTime) override {
		for (const auto& entityId : _entities) {
			auto& c = _collisionComponents[entityId];
			auto& t = _transformComponents[entityId];

			if (c.CollisionWith != nullptr) {
				t.Position.X -= (t.CurrentDelta.X * 3.f);
				t.Position.Y -= (t.CurrentDelta.Y * 3.f);
			}
		}
	}

private:
	EntityComponentArray<CollisionComponent>& _collisionComponents;
	EntityComponentArray<TransformationComponent>& _transformComponents;
};

}

#endif
