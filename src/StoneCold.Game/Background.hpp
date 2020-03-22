
#ifndef STONECOLD_BACKGROUND_H
#define STONECOLD_BACKGROUND_H

#include "Entity.hpp"
#include "TextureResource.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

class Background : public Entity {
public:
	Background(EntityComponentSystem* ecs, TextureResource* texture, SDL_Rect srcRect, SDL_FRect destRect)
		: Entity(ecs), _texture(texture) {

		// Create a fixed Sprite Component, to draw the Background
		auto flip = SDL_RendererFlip::SDL_FLIP_NONE;
		AddComponent<ScreenPositionComponent>({ srcRect, destRect });
		AddComponent<SpriteComponent>({ _texture->GetTextureSDL(), flip });
	}

private:
	TextureResource* _texture;
};

}

#endif
