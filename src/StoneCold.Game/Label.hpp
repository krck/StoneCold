
#ifndef STONECOLD_LABEL_H
#define STONECOLD_LABEL_H

#include "Entity.hpp"
#include "TextureResource.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

class Label : public Entity {
public:
	Label(EntityComponentSystem* ecs, TextureResource* texture, Vec2i surfaceSize, SDL_FRect destRect)
		: Entity(ecs), _texture(texture) {

		// Set the Source rectange (Pixels to take from the Texture) is the original surface width/heigt
		SDL_Rect srcRect = { 0, 0, surfaceSize.X, surfaceSize.Y };

		// Create a fixed Sprite Component, to draw the Label
		auto flip = SDL_RendererFlip::SDL_FLIP_NONE;
		AddComponent<ScreenPositionComponent>({ srcRect, destRect });
		AddComponent<SpriteComponent>({ _texture->GetTextureSDL(), flip });
	}

private:
	TextureResource* _texture;
};

}

#endif
