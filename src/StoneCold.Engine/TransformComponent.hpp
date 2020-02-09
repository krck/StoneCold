
#ifndef STONECOLD_TRANSFORMCOMPONENT_H
#define STONECOLD_TRANSFORMCOMPONENT_H

#include "Component.hpp"
#include "Vec2.hpp"

namespace StoneCold::Engine {

//
// 2D Transformation Component
// Dependent on: ---
// 
// Contains position, velocity (acceleration in each axis) and dimension (width/height) vectors
// and additionally some information (factors) for scaling and the speed of the GameObject
//
class TransformComponent : public IComponent {
public:
	Vec2 Position;
	Vec2 Velocity;
	Vec2 Dimensions;
	int Scale = 1;
	int Speed = 100;

	TransformComponent(Vec2 pos, Vec2 dim, int scale, int speed)
		: Position(pos), Velocity(Vec2()), Dimensions(dim), Scale(scale), Speed(speed) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
		Velocity.X = 0;
		Velocity.Y = 0;
	}

	void Update(uint frameTime) override {
		// Add a simple form of numerical integration (Explicit Euler) to speeds at different FPSs
		// (Explicit Euler works well as long as the speeds is constant or the frameTime is low)
		float deltaSec = frameTime / 1000.0f;
		Position.X += (Velocity.X * deltaSec) * Speed;
		Position.Y += (Velocity.Y * deltaSec) * Speed;
	}
};

}

#endif
