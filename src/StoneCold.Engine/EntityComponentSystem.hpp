
#ifndef STONECOLD_ENTITYCOMPONENTSYSTEM_H
#define STONECOLD_ENTITYCOMPONENTSYSTEM_H

#include "Settings.hpp"
#include "Components.hpp"
#include "TransformationSystem.hpp"
#include "EntityComponentArray.hpp"
#include <unordered_map>
#include <typeindex>
#include <typeinfo>
#include <array>
#include <queue>

namespace StoneCold::Engine {

using namespace StoneCold::Base;

const uint32 MAX_ENTITIES = 5000;

//
// Entity-Component Manager
// based on: https://austinmorlan.com/posts/entitycomponent_system/
//
// Managing the creation and destruction of Entities. This includes distributing
// Entity IDs and keeping record of which IDs are in use and which are not.
//
class EntityComponentSystem {
public:
	EntityComponentSystem()
		: _availableEntities(std::queue<entity>())
		, _entityComponents(std::array<mask, MAX_ENTITIES>())
		, _componentMasks(std::unordered_map<std::type_index, mask>())
		, _componentArrays(std::unordered_map<std::type_index, std::shared_ptr<IEntityComponentArray>>())
		, _systems(std::unordered_map<std::type_index, std::shared_ptr<System>>()) { }

	EntityComponentSystem(const EntityComponentSystem&) = delete;
	EntityComponentSystem& operator=(const EntityComponentSystem&) = delete;

	void Init() {
		// Initialize the queue with all possible entity IDs
		for (entity entity = 0; entity < MAX_ENTITIES; ++entity)
			_availableEntities.push(entity);

		// Add this component type to the component type map (hardcoded for each Component)
		_componentMasks.insert({ std::type_index(typeid(TransformationComponent_x)), COMP_MASK_TRANSFORMATION });
		_componentMasks.insert({ std::type_index(typeid(VelocityComponent_x)), COMP_MASK_VELOCITY });
		// ...

		// Create a ComponentArray pointer and add it to the component arrays map (hardcoded for each Component)
		_componentArrays.insert({ std::type_index(typeid(TransformationComponent_x)), std::make_shared<EntityComponentArray<TransformationComponent_x>>(MAX_ENTITIES) });
		_componentArrays.insert({ std::type_index(typeid(VelocityComponent_x)), std::make_shared<EntityComponentArray<VelocityComponent_x>>(MAX_ENTITIES) });
		// ...

		// Create the Systems
		const mask siMask = (COMP_MASK_TRANSFORMATION | COMP_MASK_VELOCITY);
		auto tansFormSysPtr = std::make_shared<TransformationSystem>(siMask, *GetComponentArray<TransformationComponent_x>(), *GetComponentArray<VelocityComponent_x>());
		_systems.insert({ std::type_index(typeid(TransformationSystem)), tansFormSysPtr });
		// ...
	}

	entity CreateEntity() {
		if (_availableEntities.size() == 0)
			throw std::out_of_range("No more Entity Ids available");
		// Get the first available ID of the queue
		entity id = _availableEntities.front();
		_availableEntities.pop();
		// Reset the new Entities ComponentMask
		_entityComponents[id] = 0;
		return id;
	}

	void DestroyEntity(entity entity) {
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : _componentArrays) {
			auto const& component = pair.second;
			component->DestroyEntity(entity); // INTERFACE IS NEEDED FOR THIS!
		}
		// Invalidate the destroyed entity's ComponentMask
		// Put the destroyed ID at the back of the queue
		_entityComponents[entity] = 0;
		_availableEntities.push(entity);
	}

	template<typename T>
	void AddComponent(entity entity, T component) {
		// Add the Entity (and the component values) to the specific Component Array
		GetComponentArray<T>()->insert(entity, component);
		// Add the Component Flag to the mask (OR bitmask with the current value)
		_entityComponents[entity] |= _componentMasks[std::type_index(typeid(T))];
		UpdateSystems(entity, _entityComponents[entity]);
	}

	template<typename T>
	void RemoveComponent(entity entity) {
		// Remove the Entitiy (and its component values) from a specific Component Array
		GetComponentArray<T>()->erase(entity);
		// Remove the Component Flag from the mask (AND with the inverse of the bitmask)
		_entityComponents[entity] &= ~_componentMasks[std::type_index(typeid(T))];
		UpdateSystems(entity, _entityComponents[entity]);
	}

	template<typename T>
	inline T* GetSystem() { return static_cast<T*>(_systems[std::type_index(typeid(T))].get()); }

	inline size_t AvailableEntitiesSize() const { return _availableEntities.size(); }

	~EntityComponentSystem() = default;

private:
	// Convenience function to get the statically casted pointer to the ComponentArray of type T.
	template<typename T>
	inline EntityComponentArray<T>* GetComponentArray() {
		return dynamic_cast<EntityComponentArray<T>*>(_componentArrays[std::type_index(typeid(T))].get());
	}

	void UpdateSystems(entity entity, mask entityComponentMask) {
		// Notify each system that an Entity's ComponentMask changed
		for (auto const& pair : _systems) {
			auto const& system = pair.second;
			auto const& systemMask = system->GetComponentMask();
			// Check if the Entity's ComponentMask matches the System and add (or remove)
			if ((entityComponentMask & systemMask) == systemMask)
				system->AddEntity(entity);
			else
				system->RemoveEntity(entity);
		}
	}

private:
	// Entity variables:
	// All possible Entity-Ids and all Entity-Component masks (Check which Entity has which Components)
	std::queue<entity> _availableEntities;
	std::array<mask, MAX_ENTITIES> _entityComponents;
	// Component variables:
	// All Component-Struct - Component-Mask assignments and all EntityComponentArrays holding the actual Component data
	std::unordered_map<std::type_index, mask> _componentMasks;
	std::unordered_map<std::type_index, std::shared_ptr<IEntityComponentArray>> _componentArrays;
	// System variables:
	std::unordered_map<std::type_index, std::shared_ptr<System>> _systems;
};

}

#endif
