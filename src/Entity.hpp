
#ifndef STONECOLD_ENTITY_H
#define STONECOLD_ENTITY_H

#include "Settings.hpp"

namespace StoneCold {

//
// Entity
// Interface for all renderable Game-Objects (Sprites, Map-Tiles, GUI elements, ...)
// 
class Entity {
public:
	Entity(SDL_Renderer* renderer) : _renderer(renderer) {}

	virtual void Update(uint timestampOld, uint timestampNew) = 0;
	virtual void Render() = 0;

protected:
	SDL_Renderer* _renderer;
};

}

#endif
