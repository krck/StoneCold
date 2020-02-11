
#ifndef STONECOLD_PLAYERCHARACTER_H
#define STONECOLD_PLAYERCHARACTER_H

#include "TransformComponent.hpp"
#include "SpriteComponentMoving.hpp"
#include "KeyboardComponent.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;

class PlayerCharacter : public GameObject {
public:
	PlayerCharacter(SDL_Renderer* renderer, SDL_Texture* texture, Vec2 position, Vec2 dimension, int scale, int speed) {
		// Create the Components needed by the PlayerCharacter
		auto t = TransformComponent(position, dimension, scale, speed);
		auto s = SpriteComponentMoving(renderer, texture, SDL_Rect(), SDL_FRect());
		auto k = KeyboardComponent();

		// Add the Components. The order is important!
		AddComponent<TransformComponent>(std::make_shared<TransformComponent>(t));
		AddComponent<KeyboardComponent>(std::make_shared<KeyboardComponent>(k));
		AddComponent<SpriteComponentMoving>(std::make_shared<SpriteComponentMoving>(s));
	}
};

}

#endif
