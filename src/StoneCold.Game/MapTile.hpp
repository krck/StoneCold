
#ifndef STONECOLD_MAPTILE_H
#define STONECOLD_MAPTILE_H

#include "Vec2.hpp"
#include "TextureResource.hpp"
#include "SpriteComponentFixed.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Resources;

class MapTile : public GameObject {
public:
	MapTile(SDL_Renderer* renderer, TextureResource* texture, SDL_Rect textureFrame, Vec2 position, int scale, SDL_RendererFlip flip, MapTileTypes tileType) {
		_texture = texture;

		// Set the Source rectange frame inside the texture (Pixels to take, from the .png)
		SDL_Rect src = textureFrame;
		// Set the Destination rectangle with the actual position on screen with scaling (Where to put the Pixels)
		SDL_FRect dest = { position.X, position.Y, static_cast<float>(src.w * scale), static_cast<float>(src.h * scale) };

		// Add the CollisionComponent in case its a Wall-Tile
		if (static_cast<int>(tileType) > static_cast<int>(MapTileTypes::Portal)) {
			auto c = CollisionComponent("wall", true, Vec2(), dest);
			AddComponent<CollisionComponent>(std::make_shared<CollisionComponent>(c));
		}

		// Create a fixed Sprite Component, to draw the MapTile
		auto s = SpriteComponentFixed(renderer, _texture->GetTextureSDL(), src, dest, flip);
		AddComponent<SpriteComponentFixed>(std::make_shared<SpriteComponentFixed>(s));
	}

private:
	TextureResource* _texture;
};

}

#endif
