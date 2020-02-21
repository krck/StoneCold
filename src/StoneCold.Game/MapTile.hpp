
#ifndef STONECOLD_MAPTILE_H
#define STONECOLD_MAPTILE_H

#include "Vec2.hpp"
#include "TextureResource.hpp"
#include "SpriteComponentFixed.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

class MapTile : public GameObject {
public:
	MapTile(SDL_Renderer* renderer, TextureResource* texture, Vec2 position, Vec2 dimension, SDL_Rect srcRect, SDL_RendererFlip flip, MapTileTypes tileType) {
		_texture = texture;

		// Fixed src_rect (Pixels to take, from the .png) and dest_rect (Where to put the Pixels)
		SDL_Rect src = { srcRect.x, srcRect.y, (int)dimension.X, (int)dimension.Y };
		SDL_FRect dest = { position.X, position.Y, dimension.X, dimension.Y };

		// Add the CollisionComponent in case its a Wall-Tile (all MapTileTypes > 8)
		if (static_cast<int>(tileType) > 8) {
			auto c = CollisionComponent("wall", true, { position.X, position.Y, dimension.X, dimension.Y });
			AddComponent<CollisionComponent>(std::make_shared<CollisionComponent>(c));
		}

		// Create the Components needed by the MapTile
		auto s = SpriteComponentFixed(renderer, _texture->GetTextureSDL(), src, dest, flip, 3);

		// Add the Components. The order is important!
		AddComponent<SpriteComponentFixed>(std::make_shared<SpriteComponentFixed>(s));
	}

private:
	TextureResource* _texture;
};

}

#endif
