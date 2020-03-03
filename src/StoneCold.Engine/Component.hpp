
#ifndef STONECOLD_COMPONENT_H
#define STONECOLD_COMPONENT_H

#include "SDL_Base.hpp"
#include "Types.hpp"
#include <vector>

namespace StoneCold::Engine {

class Entity;

//
// Component Interface
//
class Component {
protected:
	Entity* _entity;

public:
	Component() : _entity(nullptr) { }

	virtual void Init(Entity* entity) { _entity = entity; }
	virtual void HandleInputEvent(const std::vector<uint8>& keyStates) { }
	virtual void Update(uint frameTime) { }
	virtual void Render(SDL_FRect camera) { }

	inline Entity* GetEntity() { return _entity; }

	virtual ~Component() {}
};

}

#endif
