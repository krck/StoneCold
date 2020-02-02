
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
// 
//
class IComponent {
protected:
	GameObject* _gameObject;

public:
	IComponent() : _gameObject(nullptr) { }

	virtual void Init(GameObject* gameObject) { _gameObject = gameObject; }
	virtual void HandleEvent(const SDL_Event& event) { }
	virtual void Update(uint timestampOld, uint timestampNew) { }
	virtual void Render() { }

	// Virtual Destructor ?
	virtual ~IComponent() {}
};

//
//
//
class GameObject {
private:
	std::unordered_map<std::type_index, std::shared_ptr<IComponent>> _components;

public:
	GameObject() : _components(std::unordered_map<std::type_index, std::shared_ptr<IComponent>>()) { }

	// Pass on main-loop Events to all Components
	void HandleEvent(const SDL_Event& event) { for (auto& iter : _components) iter.second->HandleEvent(event); }
	void Update(uint timestampOld, uint timestampNew) { for (auto& iter : _components) iter.second->Update(timestampOld, timestampNew); }
	void Render() { for (auto& iter : _components) iter.second->Render(); }

	//
	// Add a new Component to the GameObject based on the Component Type
	// Each GameObject can have any Component but only one active instance of each Type
	// (type_index is a wrapper class around a std::type_info object, that can be used as index)
	//
	template<typename T>
	void AddComponent(std::shared_ptr<IComponent>&& component) {
		component->Init(this);
		_components[std::type_index(typeid(T))].swap(component);
	}

	template<typename T>
	T* GetComponent() { return static_cast<T*>(_components[std::type_index(typeid(T))].get()); }

	template<typename T>
	bool HasComponent() const { return (_components.find(std::type_index(typeid(T))) != _components.end()); }
};

}

#endif
