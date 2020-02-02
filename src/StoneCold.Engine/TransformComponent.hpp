
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
	Vec2i Position;
	Vec2i Velocity;
	Vec2i Dimensions;
	int Scale = 1;
	int Speed = 3;

	TransformComponent(Vec2i pos, Vec2i dim, int scale, int speed)
		: Position(pos), Velocity(Vec2i()), Dimensions(dim), Scale(scale), Speed(speed) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
		Velocity.X = 0;
		Velocity.Y = 0;
	}

	void Update(uint timestampOld, uint timestampNew) override {
		Position.X += Velocity.X * Speed;
		Position.Y += Velocity.Y * Speed;
	}
};

}

#endif
