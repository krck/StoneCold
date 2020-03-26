
#ifndef STONECOLD_SCREENPOSITIONSYSTEM_H
#define STONECOLD_SCREENPOSITIONSYSTEM_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentArray.hpp"

namespace StoneCold::Engine {

class ScreenPositionSystem : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a Velocity (!!!), ScreenPosition and Sprite Component will be updated with this System
	//
	ScreenPositionSystem(EntityComponentArray<TransformationComponent>& transf, EntityComponentArray<ScreenPositionComponent>& position)
		: System((GetComponentMask<VelocityComponent>() | GetComponentMask<TransformationComponent>() | GetComponentMask<ScreenPositionComponent>()))
		, _transformComponents(transf), _positionComponents(position) { }

	ScreenPositionSystem(const ScreenPositionSystem&) = delete;
	ScreenPositionSystem& operator=(const ScreenPositionSystem&) = delete;

	virtual void Update(uint32 frameTime) override {
		for (const auto& entityId : _entities) {
			auto& t = _transformComponents[entityId];
			auto& p = _positionComponents[entityId];

			// Update the Sprite position on screen based on the transformations
			p.DestRect.x = t.Position.X;
			p.DestRect.y = t.Position.Y;
			p.DestRect.w = t.Dimension.X * t.Scale;
			p.DestRect.h = t.Dimension.Y * t.Scale;
		}
	}

private:
	EntityComponentArray<TransformationComponent>& _transformComponents;
	EntityComponentArray<ScreenPositionComponent>& _positionComponents;
};

}

#endif
