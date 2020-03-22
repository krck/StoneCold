
#ifndef STONECOLD_ENTITY_H
#define STONECOLD_ENTITY_H

#include "Types.hpp"
#include "EntityComponentSystem.hpp"

namespace StoneCold::Engine {

using namespace StoneCold::Base;

//
// Entity (entityId wrapper)
//
// This is a base class for any GameObject or GuiObject holding a 
// entityId within the ECS and allows to add or remove Components
//
class Entity {
public:
	Entity(EntityComponentSystem* ecs) : _ecs(ecs), _entityId(ecs->CreateEntity()) { }

	template<typename T>
	inline void AddComponent(T component) { _ecs->AddComponent<T>(_entityId, component); }

	template<typename T>
	inline void RemoveComponent() { _ecs->RemoveComponent<T>(_entityId); }

	virtual ~Entity() { _ecs->DestroyEntity(_entityId); }

private:
	const entityId _entityId;
	EntityComponentSystem* _ecs;
};

}

#endif
