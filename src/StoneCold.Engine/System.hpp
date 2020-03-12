
#ifndef STONECOLD_SYSTEM_H
#define STONECOLD_SYSTEM_H

#include "SDL_Base.hpp"
#include "Types.hpp"
#include "EntityComponentArray.hpp"
#include "Components.hpp"
#include <vector>

namespace StoneCold::Engine {

using namespace StoneCold::Base;

//
// System Interface
//
class System {
public:
	System(mask componentMask) : _componentMask(componentMask) { }

	virtual void HandleInputEvent(const std::vector<uint8>& keyStates) { }
	virtual void Update(uint32 frameTime) { }
	virtual void Render(SDL_FRect camera) { }

	inline mask GetComponentMask() const { return _componentMask; }

	void AddEntity();
	void RemoveEntity();

	virtual ~System() {}

protected:
	const mask _componentMask;
	std::vector<entity> _entities;
};


//class SystemImplementation : public System {
//public:
//	// ...
//	SystemImplementation(mask componentMask, EntityComponentArray<TransformComponent_x>* trans, EntityComponentArray<AnimationComponent_x>* anim)
//		: System(componentMask), _transformComponents(trans), _animationComponents(anim) { }
//
//	virtual void Update(uint32 frameTime) override {
//		// Update all
//		for (auto const& entity : _entities) {
//			auto& transf = _transformComponents[entity];
//			auto& anima = _animationComponents[entity];
//			// ...
//		}
//	}
//
//	// ...
//
//private:
//	EntityComponentArray<TransformComponent_x>* _transformComponents;
//	EntityComponentArray<AnimationComponent_x>* _animationComponents;
//};

}

#endif
