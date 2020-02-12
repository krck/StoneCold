
#ifndef STONECOLD_PLAYERCHARACTER_H
#define STONECOLD_PLAYERCHARACTER_H

#include "TransformComponent.hpp"
#include "SpriteComponentAnimated.hpp"
#include "KeyboardComponent.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;

class PlayerCharacter : public GameObject {
public:
	PlayerCharacter(SDL_Renderer* renderer, SDL_Texture* texture, const std::unordered_map<std::string, Animation>& animations, Vec2 position, Vec2 dimension, int scale, int speed) {
		// Create the Components needed by the PlayerCharacter
		auto t = TransformComponent(position, dimension, scale, speed);
		auto k = KeyboardComponent();
		auto s = SpriteComponentAnimated(renderer, texture, animations, SDL_FRect());

		// Add the Components. The order is important!
		AddComponent<TransformComponent>(std::make_shared<TransformComponent>(t));
		AddComponent<KeyboardComponent>(std::make_shared<KeyboardComponent>(k));
		AddComponent<SpriteComponentAnimated>(std::make_shared<SpriteComponentAnimated>(s));
	}
};

}

#endif
