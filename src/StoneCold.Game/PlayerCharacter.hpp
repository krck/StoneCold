
#ifndef STONECOLD_PLAYERCHARACTER_H
#define STONECOLD_PLAYERCHARACTER_H

#include "Entity.hpp"
#include "TextureResource.hpp"
#include "AnimationResource.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

class PlayerCharacter : public Entity {
public:
	PlayerCharacter(EntityComponentSystem* ecs, TextureResource* texture, AnimationResource* animation, Vec2 position, Vec2 dimension, uint32 scale, uint32 speed)
		: Entity(ecs), _texture(texture), _animation(animation) {

		// Set the Source rectange frame inside the texture (Pixels to take, from the .png)
		SDL_Rect defaultSrcRect = { 0, 0, static_cast<int>(floorf(dimension.X * scale)), static_cast<int>(floorf(dimension.Y * scale)) };
		// Set the Destination rectangle with the actual position on screen with scaling (Where to put the Pixels)
		SDL_FRect defaultDestRect = { position.X, position.Y, dimension.X * scale, dimension.Y * scale };

		// Set a default Animation
		//a.SetCurrentAnimation("idle");

		// Create the Components needed by the PlayerCharacter
		auto flip = SDL_RendererFlip::SDL_FLIP_NONE;
		AddComponent<VelocityComponent>({ Vec2() });
		AddComponent<TransformationComponent>({ position, dimension, speed, speed, scale });
		AddComponent<CollisionComponent>({ "player", Vec2(14.f, 18.f), defaultDestRect, nullptr, false });
		AddComponent<AnimationComponent>({ _animation->Animations, nullptr, 0, 0 });
		AddComponent<ScreenPositionComponent>({ defaultSrcRect, defaultDestRect });
		AddComponent<SpriteComponent>({ _texture->GetTextureSDL(), flip });
	}

private:
	TextureResource* _texture;
	AnimationResource* _animation;
};

}

#endif
