
#ifndef STONECOLD_ENTITYCOMPONENTSYSTEM_H
#define STONECOLD_ENTITYCOMPONENTSYSTEM_H

#include "SDL_Base.hpp"
#include "Settings.hpp"
#include "System.hpp"
#include <typeindex>
#include <typeinfo>
#include <array>
#include <queue>

namespace StoneCold::Engine {

using namespace StoneCold::Base;

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
		_componentMasks.insert({ std::type_index(typeid(AnimationComponent_x)),	COMP_MASK_ANIMATION });
		// ...

		// Create a ComponentArray pointer and add it to the component arrays map (hardcoded for each Component)
		_componentArrays.insert({ std::type_index(typeid(AnimationComponent_x)), std::make_shared<EntityComponentArray<AnimationComponent_x>>(MAX_ENTITIES) });
		// ...

		// Create the Systems
		//_systems.insert()
	}

	entity CreateEntity() {
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
			component->EntityDestroyed(entity); // INTERFACE IS NEEDED FOR THIS!
		}

		// Invalidate the destroyed entity's ComponentMask
		_entityComponents[entity] = 0;
		// Put the destroyed ID at the back of the queue
		_availableEntities.push(entity);
	}

	template<typename T>
	void AddComponent(entity entity, T component) {
		// Add a component to the array for an Entity and update the ComponentMask
		GetComponentArray<T>()->insert(entity, component);

		// Add Component flag to the mask (OR bitmask with the current value)
		_entityComponents[entity] |= _componentMasks[std::type_index(typeid(T))];
		UpdateEntityComponents(entity, _entityComponents[entity]);
	}

	template<typename T>
	void RemoveComponent(entity entity) {
		// Remove a component from the array for an Entity and update the ComponentMask
		GetComponentArray<T>()->erase(entity);

		// Remove Component Flag, from the mask (AND with the inverse of the bitmask)
		_entityComponents[entity] &= ~_componentMasks[std::type_index(typeid(T))];
		UpdateEntityComponents(entity, _entityComponents[entity]);
	}

	template<typename T>
	inline T* GetSystem() { return static_cast<T*>(_systems[std::type_index(typeid(T))].get()); }

	~EntityComponentSystem() = default;

private:
	// Convenience function to get the statically casted pointer to the ComponentArray of type T.
	template<typename T>
	inline EntityComponentArray<T>* GetComponentArray() {
		return dynamic_cast<EntityComponentArray<T>*>(_componentArrays[std::type_index(typeid(T))].get());
	}

	void UpdateEntityComponents(entity entity, mask entityComponents) {
		// Notify each system that an entity's signature changed
		//for (auto const& pair : _systems) {

		//	auto const& type = pair.first;
		//	auto const& system = pair.second;
		//	auto const& systemSignature = mSignatures[type];

		//	// Entity signature matches system signature - insert into set
		//	if ((entitySignature & systemSignature) == systemSignature) {
		//		system->mEntities.insert(entity);
		//	}
		//	// Entity signature does not match system signature - erase from set
		//	else {
		//		system->mEntities.erase(entity);
		//	}
		//}
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
	// All Systems
	std::unordered_map<std::type_index, std::shared_ptr<System>> _systems;
};

}

#endif
