
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
	PlayerCharacter(SDL_Renderer* renderer, TextureResource* texture, const std::unordered_map<std::string, Animation>& animations, Vec2 position, Vec2 dimension, int scale, int speed) {
		_texture = texture;
		
		// Create the Components needed by the PlayerCharacter
		auto t = TransformComponent(position, dimension, scale, speed);
		auto s = SpriteComponentAnimated(renderer, _texture->GetTextureSDL(), animations, SDL_FRect());
		auto k = KeyboardComponent();
		s.SetCurrentAnimation("idle");

		// Add the Components. The order is important!
		AddComponent<TransformComponent>(std::make_shared<TransformComponent>(t));
		AddComponent<SpriteComponentAnimated>(std::make_shared<SpriteComponentAnimated>(s));
		AddComponent<KeyboardComponent>(std::make_shared<KeyboardComponent>(k));

	}

private:
	TextureResource* _texture;

};

}

#endif
