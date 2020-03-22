
#ifndef STONECOLD_TRANSFORMATIONSYSTEM_H
#define STONECOLD_TRANSFORMATIONSYSTEM_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentArray.hpp"

namespace StoneCold::Engine {

class TransformationSystem : public System {
public:
	TransformationSystem(mask componentMask, EntityComponentArray<TransformationComponent>& trans, EntityComponentArray<VelocityComponent>& velocity)
		: System(componentMask), _transformComponents(trans), _velocityComponents(velocity) { }

	TransformationSystem(const TransformationSystem&) = delete;
	TransformationSystem& operator=(const TransformationSystem&) = delete;

	virtual void Update(uint32 frameTime) override {
		for (const auto& entityId : _entities) {
			//auto& transf = _transformComponents[entity]; //->at(entity);
			//auto& velocity = _velocityComponents[entity];
			//velocity.Velocity += (transf.Scale + transf.Speed);
		}
	}

private:
	EntityComponentArray<TransformationComponent>& _transformComponents;
	EntityComponentArray<VelocityComponent>& _velocityComponents;
};

}

#endif
