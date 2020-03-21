
#ifndef STONECOLD_SYSTEM_H
#define STONECOLD_SYSTEM_H

#include "SDL_Base.hpp"
#include "Types.hpp"
#include <algorithm>
#include <vector>

namespace StoneCold::Engine {

using namespace StoneCold::Base;

//
// System Interface
//
class System {
public:
	System(mask componentMask) : _componentMask(componentMask) { }
	System(const System&) = delete;
	System& operator=(const System&) = delete;

	virtual void HandleInputEvent(const std::vector<uint8>& keyStates) { }
	virtual void Update(uint32 frameTime) { }
	virtual void Render(SDL_FRect camera) { }

	inline mask GetComponentMask() const { return _componentMask; }
	inline size_t GetEntitiesSize() const { return _entities.size(); }

	inline void AddEntity(entity entity) { _entities.push_back(entity); }
	inline void RemoveEntity(entity entity) { _entities.erase(std::remove(_entities.begin(), _entities.end(), entity), _entities.end()); }

	virtual ~System() {}

protected:
	const mask _componentMask;
	std::vector<entity> _entities;
};

}

#endif
