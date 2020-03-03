
#ifndef STONECOLD_PLAYERCHARACTER_H
#define STONECOLD_PLAYERCHARACTER_H

#include "Entity.hpp"
#include "TransformComponent.hpp"
#include "KeyboardComponent.hpp"
#include "SpriteComponentMoving.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

class PlayerCharacter : public Entity {
public:
	PlayerCharacter(SDL_Renderer* renderer, TextureResource* texture, AnimationResource* animation, Vec2 position, Vec2 dimension, int scale, int speed) {
		_texture = texture;
		_animation = animation;

		// Set the Source rectange frame inside the texture (Pixels to take, from the .png)
		SDL_Rect defaultSrcRect = { 0, 0, static_cast<int>(floorf(dimension.X * scale)), static_cast<int>(floorf(dimension.Y * scale)) };
		// Set the Destination rectangle with the actual position on screen with scaling (Where to put the Pixels)
		SDL_FRect defaultDestRect = { position.X, position.Y, dimension.X * scale, dimension.Y * scale };

		// Create the Components needed by the PlayerCharacter
		auto c = CollisionComponent("player", false, Vec2(14.f, 18.f), defaultDestRect);
		auto a = AnimationComponent(_animation->Animations);
		auto t = TransformComponent(position, dimension, scale, speed);
		auto s = SpriteComponentMoving(renderer, _texture->GetTextureSDL(), defaultSrcRect, defaultDestRect);
		auto k = KeyboardComponent();

		// Set a default Animation
		a.SetCurrentAnimation("idle");

		// Add the Components. The order is important!
		AddComponent<CollisionComponent>(std::make_shared<CollisionComponent>(c));
		AddComponent<AnimationComponent>(std::make_shared<AnimationComponent>(a));
		AddComponent<TransformComponent>(std::make_shared<TransformComponent>(t));
		AddComponent<KeyboardComponent>(std::make_shared<KeyboardComponent>(k));
		AddComponent<SpriteComponentMoving>(std::make_shared<SpriteComponentMoving>(s));
	}

private:
	TextureResource* _texture;
	AnimationResource* _animation;
};

}

#endif
