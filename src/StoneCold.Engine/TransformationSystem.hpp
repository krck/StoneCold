
#ifndef STONECOLD_TRANSFORMATIONSYSTEM_H
#define STONECOLD_TRANSFORMATIONSYSTEM_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentArray.hpp"

namespace StoneCold::Engine {

class TransformationSystem : public System {
public:
	TransformationSystem(mask componentMask, EntityComponentArray<TransformationComponent_x>& trans, EntityComponentArray<VelocityComponent_x>& velocity)
		: System(componentMask), _transformComponents(trans), _velocityComponents(velocity) { }

	TransformationSystem(const TransformationSystem&) = delete;
	TransformationSystem& operator=(const TransformationSystem&) = delete;

	virtual void Update(uint32 frameTime) override {
		for (const auto& entity : _entities) {
			//auto& transf = _transformComponents[entity]; //->at(entity);
			//auto& velocity = _velocityComponents[entity];
			//velocity.Velocity += (transf.Scale + transf.Speed);
		}
	}

private:
	EntityComponentArray<TransformationComponent_x>& _transformComponents;
	EntityComponentArray<VelocityComponent_x>& _velocityComponents;
};

}

#endif
