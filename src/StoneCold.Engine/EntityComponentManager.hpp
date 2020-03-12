
#ifndef STONECOLD_ENTITYCOMPONENTMANAGER_H
#define STONECOLD_ENTITYCOMPONENTMANAGER_H

#include "SDL_Base.hpp"
#include "Settings.hpp"
#include "EntityComponentArray.hpp"
#include <typeindex>
#include <typeinfo>
#include <array>
#include <queue>

namespace StoneCold::Engine {

using namespace StoneCold::Base;

//
// Entity-Component Manager
// based on: https://austinmorlan.com/posts/entity_component_system/
//
// Managing the creation and destruction of Entities. This includes distributing
// Entity IDs and keeping record of which IDs are in use and which are not.
//
class EntityComponentManager {
public:
	EntityComponentManager()
		: _availableEntities(std::queue<Entity_>()), _entityComponentMasks(std::array<ComponentMask, MAX_ENTITIES>())
		, _componentArrays(std::unordered_map<std::type_index, std::shared_ptr<IEntityComponentArray>>())
		, _componentTypes(std::unordered_map<std::type_index, ComponentType>()) { }

	EntityComponentManager(const EntityComponentManager&) = delete;
	EntityComponentManager& operator=(const EntityComponentManager&) = delete;

	void Init() {
		// Initialize the queue with all possible entity IDs
		for (Entity_ entity = 0; entity < MAX_ENTITIES; ++entity)
			_availableEntities.push(entity);

		//// Add this component type to the component type map (hardcoded for each Component)
		//_componentTypes.insert({ std::type_index(typeid(GravityComponent)), 0 });
		//_componentTypes.insert({ std::type_index(typeid(TransformComponent)), 1 });
		//// Create a ComponentArray pointer and add it to the component arrays map (hardcoded for each Component)
		//_componentArrays.insert({ std::type_index(typeid(GravityComponent)), std::make_shared<EntityComponentArray<GravityComponent>>() });
		//_componentArrays.insert({ std::type_index(typeid(TransformComponent)), std::make_shared<EntityComponentArray<TransformComponent>>() });
	}

	Entity_ CreateEntity() {
		// Get the first available ID of the queue
		Entity_ id = _availableEntities.front();
		_availableEntities.pop();
		// Reset the new Entities Component-ComponentMask
		_entityComponentMasks[id] = ComponentMask();
		return id;
	}

	void DestroyEntity(Entity_ entity) {
		// Notify each component array that an entity has been destroyed
		// If it has a component for that entity, it will remove it
		for (auto const& pair : _componentArrays) {
			auto const& component = pair.second;
			component->EntityDestroyed(entity); // INTERFACE IS NEEDED FOR THIS!
		}

		// Invalidate the destroyed entity's ComponentMask
		_entityComponentMasks[entity].reset();
		// Put the destroyed ID at the back of the queue
		_availableEntities.push(entity);
	}

	template<typename T>
	void AddComponent(Entity_ entity, T component) {
		// Add a component to the array for an Entity and update the ComponentMask
		GetComponentArray<T>()->insert(entity, component);
		_entityComponentMasks[entity].set(GetComponentType<T>(), true);
	}

	template<typename T>
	void RemoveComponent(Entity_ entity) {
		// Remove a component from the array for an Entity and update the ComponentMask
		GetComponentArray<T>()->erase(entity);
		_entityComponentMasks[entity].set(GetComponentType<T>(), false);
	}

	template<typename T>
	inline T& GetComponent(Entity_ entity) {
		// Get a reference to a component from the array for an entity
		return GetComponentArray<T>()->GetData(entity);
	}

	template<typename T>
	inline ComponentType GetComponentType() { return _componentTypes[std::type_index(typeid(T))]; }

	inline ComponentMask GetComponentMask(Entity_ entity) const { return _entityComponentMasks[entity]; }

	~EntityComponentManager() = default;

private:
	// Convenience function to get the statically casted pointer to the ComponentArray of type T.
	template<typename T>
	inline EntityComponentArray<T>* GetComponentArray() { return dynamic_cast<EntityComponentArray<T>*>(_componentArrays[std::type_index(typeid(T))].get()); }

private:
	// Entity variables
	std::queue<Entity_> _availableEntities;
	std::array<ComponentMask, MAX_ENTITIES> _entityComponentMasks;
	// Component variables
	std::unordered_map<std::type_index, ComponentType> _componentTypes;
	std::unordered_map<std::type_index, std::shared_ptr<IEntityComponentArray>> _componentArrays;
};

}

#endif
