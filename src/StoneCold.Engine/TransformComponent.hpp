
#ifndef STONECOLD_TRANSFORMCOMPONENT_H
#define STONECOLD_TRANSFORMCOMPONENT_H

#include "Entity.hpp"
#include "CollisionComponent.hpp"
#include "Vec2.hpp"

namespace StoneCold::Engine {

//
// 2D Transformation Component
// Required: ---
// Optional: CollisionComponent
// 
// Contains position, velocity (acceleration in each axis) and dimension (width/height) vectors
// and additionally some information (factors) for scaling and the speed of the Entity
//
class TransformComponent : public Component {
public:
	Vec2 Position;
	Vec2 Velocity;
	Vec2 Dimensions;
	const int BaseSpeed;
	int Speed;
	int Scale;
private:
	CollisionComponent* _collisionComponent;

public:
	TransformComponent(Vec2 pos, Vec2 dim, int scale, int speed)
		: _collisionComponent(nullptr), Position(pos), Velocity(Vec2()), Dimensions(dim), Scale(scale), BaseSpeed(speed), Speed(speed) { }

	void Init(Entity* entity) override {
		Component::Init(entity);

		// Get the CollisionComponent (if it has one) to update the position based on other objects
		if (_entity->HasComponent<CollisionComponent>())
			_collisionComponent = _entity->GetComponent<CollisionComponent>();

		Velocity.X = 0;
		Velocity.Y = 0;
	}

	void Update(uint frameTime) override {
		// Add a simple form of numerical integration (Explicit Euler) to speeds at different FPSs
		// (Explicit Euler works well as long as the speeds is constant or the frameTime is low)
		const float deltaSec = frameTime / 1000.0f;

		// Normalize the velocity in case of diagonal movement
		if (Velocity.X != 0 || Velocity.Y != 0)
			Velocity.normalize();

		// Update the Position, either with automatic values in case 
		// of a collision, or based on the manual input (Velocity)
		if (_collisionComponent != nullptr && _collisionComponent->HasCollision()) {
			auto recA = _collisionComponent->CollisionBox;
			auto recB = _collisionComponent->CollisionWith->CollisionBox;

			// Get the edge thats overlapping (positive or negative direction)
			bool dxP = (recA.x + recA.w - recB.x) < 10.f;
			bool dxN = (recB.x + recB.w - recA.x) < 10.f;
			bool dyP = (recA.y + recA.h - recB.y) < 10.f;
			bool dyN = (recB.y + recB.h - recA.y) < 10.f;

			// Step the overlapping Axis 1 pixel away, in the opposite direction
			Position.X += (dxN + (dxP * -1));
			Position.Y += (dyN + (dyP * -1));
		}
		else {
			// Update the position and round down to the next int
			Position.X += (Velocity.X * deltaSec) * Speed;
			Position.Y += (Velocity.Y * deltaSec) * Speed;
		}
	}
};

}

#endif
