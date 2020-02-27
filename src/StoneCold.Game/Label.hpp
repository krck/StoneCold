
#ifndef STONECOLD_LABEL_H
#define STONECOLD_LABEL_H

#include "Entity.hpp"
#include "FontResource.hpp"
#include "SpriteComponentFixed.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

class Label : public Entity {
public:
	Label(SDL_Renderer* renderer, FontResource* font, SDL_FRect destRect) {
		_font = font;

		// Create a fixed Sprite Component, to draw the Label
		auto s = SpriteComponentFixed(renderer, _texture->GetTextureSDL(), srcRect, destRect, SDL_RendererFlip::SDL_FLIP_NONE);
		AddComponent<SpriteComponentFixed>(std::make_shared<SpriteComponentFixed>(s));
	}

private:
	FontResource* _font;
};

}

#endif
