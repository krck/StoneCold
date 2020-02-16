
#ifndef STONECOLD_PLAYERCHARACTER_H
#define STONECOLD_PLAYERCHARACTER_H

#include "TransformComponent.hpp"
#include "SpriteComponentAnimated.hpp"
#include "KeyboardComponent.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

class PlayerCharacter : public GameObject {
public:
	PlayerCharacter(SDL_Renderer* renderer, TextureResource* texture, AnimationResource* animation, Vec2 position, Vec2 dimension, int scale, int speed) {
		_texture = texture;
		_animation = animation;

		// Create the Components needed by the PlayerCharacter
		auto c = CollisionComponent("player", { position.X, position.Y, dimension.X, dimension.Y });
		auto t = TransformComponent(position, dimension, scale, speed);
		auto s = SpriteComponentAnimated(renderer, _texture->GetTextureSDL(), _animation->Animations, SDL_FRect());
		auto k = KeyboardComponent();
		s.SetCurrentAnimation("idle");

		// Add the Components. The order is important!
		AddComponent<CollisionComponent>(std::make_shared<CollisionComponent>(c));
		AddComponent<TransformComponent>(std::make_shared<TransformComponent>(t));
		AddComponent<SpriteComponentAnimated>(std::make_shared<SpriteComponentAnimated>(s));
		AddComponent<KeyboardComponent>(std::make_shared<KeyboardComponent>(k));
	}

private:
	TextureResource* _texture;
	AnimationResource* _animation;
};

}

#endif
