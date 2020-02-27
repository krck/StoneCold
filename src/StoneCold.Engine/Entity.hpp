
#ifndef STONECOLD_ENTITY_H
#define STONECOLD_ENTITY_H

#include "Component.hpp"
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

namespace StoneCold::Engine {

//
// Entity
//
// A Entity can be any Game or GUI object imaginable
// The actual behaviour is defined by its Components
//
class Entity {
protected:
	std::unordered_map<std::type_index, std::shared_ptr<Component>> _components;

public:
	Entity() : _components(std::unordered_map<std::type_index, std::shared_ptr<Component>>()) { }

	// Pass on main-loop Events to all Components
	void HandleInputEvent(const std::vector<uint8>& keyStates) { for (auto& iter : _components) iter.second->HandleInputEvent(keyStates); }
	void Update(uint frameTime) { for (auto& iter : _components) iter.second->Update(frameTime); }
	void Render(SDL_FRect camera) { for (auto& iter : _components) iter.second->Render(camera); }

	//
	// Add a new Component to the Entity based on the Component Type
	// Each Entity can have any Component but only one active instance of each Type
	// (type_index is a wrapper class around a std::type_info object, that can be used as index)
	//
	template<typename T>
	void AddComponent(std::shared_ptr<Component>&& component) {
		component->Init(this);
		_components[std::type_index(typeid(T))] = std::move(component);
	}

	template<typename T>
	T* GetComponent() { return static_cast<T*>(_components[std::type_index(typeid(T))].get()); }

	template<typename T>
	bool HasComponent() const { return (_components.find(std::type_index(typeid(T))) != _components.end()); }
};

}

#endif
