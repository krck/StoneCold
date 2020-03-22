
#ifndef STONECOLD_ENTITYCOMPONENTSYSTEM_H
#define STONECOLD_ENTITYCOMPONENTSYSTEM_H

#include "Settings.hpp"
#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentArray.hpp"
#include <unordered_map>
#include <array>
#include <queue>

namespace StoneCold::Engine {

using namespace StoneCold::Base;

//
// Entity-Component-System (Manager)
// based on: https://austinmorlan.com/posts/entitycomponent_system/
//
// Managing the creation and destruction of Entities. This includes distributing
// Entity IDs and keeping record of which IDs are in use and which are not.
//
class EntityComponentSystem {
public:
	EntityComponentSystem(uint16 maxEntities)
		: _maxEntities(maxEntities)
		, _availableEntities(std::queue<entityId>())
		, _entityComponents(std::vector<mask>(maxEntities)) // Set vector size (like fixed array)
		, _componentArrays(std::unordered_map<hash, std::shared_ptr<IEntityComponentArray>>())
		, _systems(std::unordered_map<hash, std::shared_ptr<System>>()) {
		// Initialize the queue with all possible entity IDs
		for (entityId entityId = 0; entityId < _maxEntities; ++entityId)
			_availableEntities.push(entityId);
	}

	EntityComponentSystem(const EntityComponentSystem&) = delete;
	EntityComponentSystem& operator=(const EntityComponentSystem&) = delete;

	template<typename T>
	void AddSystem(std::shared_ptr<System> system) {
		//// Create the Systems
		//const mask siMask = (COMP_MASK_TRANSFORMATION | COMP_MASK_VELOCITY);
		//auto tansFormSysPtr = std::make_shared<TransformationSystem>(siMask, *GetComponentArray<TransformationComponent>(), *GetComponentArray<VelocityComponent>());
		//_systems.insert({ GetTypeHash<TransformationSystem>(), tansFormSysPtr });
		//// ...

		_systems.insert({ GetTypeHash<T>(), system });
	}

	entityId CreateEntity() {
		if (_availableEntities.size() == 0)
			throw std::out_of_range("No more Entity Ids available");

		// Get the first available ID of the queue
		entityId id = _availableEntities.front();
		_availableEntities.pop();
		// Reset the new Entities ComponentMask
		_entityComponents[id] = 0;
		return id;
	}

	void DestroyEntity(entityId entityId) {
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : _componentArrays) {
			auto const& component = pair.second;
			component->DestroyEntity(entityId); // INTERFACE IS NEEDED FOR THIS!
		}

		// Invalidate the destroyed entity's ComponentMask
		// Put the destroyed ID at the back of the queue
		_entityComponents[entityId] = 0;
		_availableEntities.push(entityId);
	}

	template<typename T>
	void AddComponent(entityId entityId, T component) {
		// Add the Entity (and the component values) to the specific Component Array
		GetComponentArray<T>()->insert(entityId, component);
		// Add the Component Flag to the mask (OR bitmask with the current value)
		_entityComponents[entityId] |= ComponentMasks[GetTypeHash<T>()];
		UpdateSystems(entityId, _entityComponents[entityId]);
	}

	template<typename T>
	void RemoveComponent(entityId entityId) {
		// Remove the Entitiy (and its component values) from a specific Component Array
		GetComponentArray<T>()->erase(entityId);
		// Remove the Component Flag from the mask (AND with the inverse of the bitmask)
		_entityComponents[entityId] &= ~ComponentMasks[GetTypeHash<T>()];
		UpdateSystems(entityId, _entityComponents[entityId]);
	}

	//
	// Get the statically casted pointer to the ComponentArray of type T
	//
	template<typename T>
	inline EntityComponentArray<T>* GetComponentArray() {
		// Check if a Component of this type was added already. If not create a ComponentArray
		if (_componentArrays.find(GetTypeHash<T>()) == _componentArrays.end()) {
			_componentArrays.insert({ GetTypeHash<T>(), std::make_shared<EntityComponentArray<T>>(_maxEntities) });
		}

		return dynamic_cast<EntityComponentArray<T>*>(_componentArrays[GetTypeHash<T>()].get());
	}

	template<typename T>
	inline T* GetSystem() {
		return (_systems.find(GetTypeHash<T>()) != _systems.end())
			? static_cast<T*>(_systems[GetTypeHash<T>()].get())
			: nullptr;
	}

	inline size_t AvailableEntitiesSize() const { return _availableEntities.size(); }

	~EntityComponentSystem() = default;

private:
	void UpdateSystems(entityId entityId, mask entityComponentMask) {
		if (_systems.empty())
			throw std::out_of_range("Register at least one System before adding or removing Components");

		// Notify each system that an Entity's ComponentMask changed
		for (auto const& pair : _systems) {
			auto const& system = pair.second;
			auto const& systemMask = system->GetComponentMask();
			// Check if the Entity's ComponentMask matches the System and add (or remove)
			if ((entityComponentMask & systemMask) == systemMask)
				system->AddEntity(entityId);
			else
				system->RemoveEntity(entityId);
		}
	}

private:
	const uint16 _maxEntities;
	// Entity variables:
	std::queue<entityId> _availableEntities;
	std::vector<mask> _entityComponents;
	// Component variables:
	std::unordered_map<hash, std::shared_ptr<IEntityComponentArray>> _componentArrays;
	// System variables:
	std::unordered_map<hash, std::shared_ptr<System>> _systems;
};

}

#endif
