
#ifndef STONECOLD_BACKGROUND_H
#define STONECOLD_BACKGROUND_H

#include "TextureResource.hpp"
#include "SpriteComponentFixed.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

class Background : public GameObject {
public:
	Background(SDL_Renderer* renderer, TextureResource* texture, SDL_Rect srcRect, SDL_FRect destRect) {
		_texture = texture;

		// Create a fixed Sprite Component, to draw the Background
		auto s = SpriteComponentFixed(renderer, _texture->GetTextureSDL(), srcRect, destRect, SDL_RendererFlip::SDL_FLIP_NONE);
		AddComponent<SpriteComponentFixed>(std::make_shared<SpriteComponentFixed>(s));
	}

private:
	TextureResource* _texture;
};

}

#endif
