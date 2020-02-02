
#ifndef STONECOLD_PLAYERCHARACTER_H
#define STONECOLD_PLAYERCHARACTER_H

#include "TransformComponent.hpp"
#include "SpriteComponent.hpp"
#include "KeyboardComponent.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;

class PlayerCharacter : public GameObject {
public:
	PlayerCharacter(SDL_Renderer* renderer, SDL_Texture* texture, Vec2i position, Vec2i dimension, int scale, int speed) {
		// Create the Components needed by the PlayerCharacter
		auto t = TransformComponent(position, dimension, scale, speed);
		auto s = SpriteComponent(renderer, texture, SDL_Rect(), SDL_Rect());
		auto k = KeyboardComponent();

		// Add the Components. The order is important!
		AddComponent<TransformComponent>(std::make_unique<TransformComponent>(t));
		AddComponent<KeyboardComponent>(std::make_unique<KeyboardComponent>(k));
		AddComponent<SpriteComponent>(std::make_unique<SpriteComponent>(s));
	}
};

}

#endif
