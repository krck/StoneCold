
#ifndef STONECOLD_TRANSFORMATIONSYSTEM_H
#define STONECOLD_TRANSFORMATIONSYSTEM_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentArray.hpp"

namespace StoneCold::Engine {

class TransformationSystem : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a Transformation and Velocity Component will be updated with this System
	//
	TransformationSystem(EntityComponentArray<TransformationComponent>& transf, EntityComponentArray<VelocityComponent>& velocity)
		: System((GetComponentMask<TransformationComponent>() | GetComponentMask<VelocityComponent>()))
		, _transformComponents(transf), _velocityComponents(velocity) { }

	TransformationSystem(const TransformationSystem&) = delete;
	TransformationSystem& operator=(const TransformationSystem&) = delete;

	virtual void Update(uint32 frameTime) override {
		// Add a simple form of numerical integration (Explicit Euler) to speeds at different FPSs
		// (Explicit Euler works well as long as the speeds is constant or the frameTime is low)
		const float deltaSec = frameTime / 1000.0f;

		for (const auto& entityId : _entities) {
			auto& t = _transformComponents[entityId];
			auto& v = _velocityComponents[entityId];

			// Normalize the velocity in case of diagonal movement
			// FIND SOME WAY TO DO THIS WITHOUT IF TO NOT DISTURB THE CACHE, OUR LORD AND SAVIOR
			if (v.Velocity.X != 0 || v.Velocity.Y != 0)
				v.Velocity.normalize();

			//	// Update the position and round down to the next int
			t.Position.X += (v.Velocity.X * deltaSec) * t.Speed;
			t.Position.Y += (v.Velocity.Y * deltaSec) * t.Speed;

			// Update the Position, either with automatic values in case 
			// of a collision, or based on the manual input (Velocity)
			//if (_collisionComponent != nullptr && _collisionComponent->HasCollision()) {
			//	auto recA = _collisionComponent->CollisionBox;
			//	auto recB = _collisionComponent->CollisionWith->CollisionBox;

			//	// Get the edge thats overlapping (positive or negative direction)
			//	bool dxP = (recA.x + recA.w - recB.x) < 10.f;
			//	bool dxN = (recB.x + recB.w - recA.x) < 10.f;
			//	bool dyP = (recA.y + recA.h - recB.y) < 10.f;
			//	bool dyN = (recB.y + recB.h - recA.y) < 10.f;

			//	// Step the overlapping Axis 1 pixel away, in the opposite direction
			//	Position.X += (dxN + (dxP * -1));
			//	Position.Y += (dyN + (dyP * -1));
			//}
			//else {
			//	// Update the position and round down to the next int
			//	Position.X += (Velocity.X * deltaSec) * Speed;
			//	Position.Y += (Velocity.Y * deltaSec) * Speed;
			//}
		}
	}

private:
	EntityComponentArray<TransformationComponent>& _transformComponents;
	EntityComponentArray<VelocityComponent>& _velocityComponents;
};

}

#endif
