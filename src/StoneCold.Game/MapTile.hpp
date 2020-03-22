
#ifndef STONECOLD_MAPTILE_H
#define STONECOLD_MAPTILE_H

#include <iostream>

#include "Entity.hpp"
#include "TextureResource.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Resources;

class MapTile : public Entity {
public:
	MapTile(EntityComponentSystem* ecs, TextureResource* texture, SDL_Rect textureFrame, Vec2 position, int scale, SDL_RendererFlip flip, MapTileTypes tileType)
		: Entity(ecs), _texture(texture) {


	}

private:
	TextureResource* _texture;
};

}

#endif
