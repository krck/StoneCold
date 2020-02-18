
#ifndef STONECOLD_COMPONENT_H
#define STONECOLD_COMPONENT_H

#include "SDL_Base.hpp"
#include "Types.hpp"
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

namespace StoneCold::Engine {

class GameObject;

//
// Component Interface
//
class IComponent {
protected:
	GameObject* _gameObject;

public:
	IComponent() : _gameObject(nullptr) { }

	virtual void Init(GameObject* gameObject) { _gameObject = gameObject; }
	virtual void HandleEvent(const uint8* keyStates) { }
	virtual void Update(uint frameTime) { }
	virtual void Render(SDL_FRect camera) { }

	inline GameObject* GetGameObject() { return _gameObject; }

	// Virtual Destructor ?
	virtual ~IComponent() {}
};

//
// GameObject base class
//
// A game object is everything that can be 
// updated and rendered (Player, NPC, ...)
// The behaviour is defined by its Components
//
class GameObject {
private:
	std::unordered_map<std::type_index, std::shared_ptr<IComponent>> _components;

public:
	GameObject() : _components(std::unordered_map<std::type_index, std::shared_ptr<IComponent>>()) { }

	// Pass on main-loop Events to all Components
	void HandleEvent(const uint8* keyStates) { for (auto& iter : _components) iter.second->HandleEvent(keyStates); }
	void Update(uint frameTime) { for (auto& iter : _components) iter.second->Update(frameTime); }
	void Render(SDL_FRect camera) { for (auto& iter : _components) iter.second->Render(camera); }

	//
	// Add a new Component to the GameObject based on the Component Type
	// Each GameObject can have any Component but only one active instance of each Type
	// (type_index is a wrapper class around a std::type_info object, that can be used as index)
	//
	template<typename T>
	void AddComponent(std::shared_ptr<IComponent>&& component) {
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
