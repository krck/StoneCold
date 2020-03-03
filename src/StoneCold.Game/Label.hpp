
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
	Label(SDL_Renderer* renderer, TextureResource* texture, SDL_Rect srcRect, SDL_FRect destRect) {
		_texture = texture;

		// Create a fixed Sprite Component, to draw the Label
		auto s = SpriteComponentFixed(renderer, _texture->GetTextureSDL(), srcRect, destRect, SDL_RendererFlip::SDL_FLIP_NONE);
		AddComponent<SpriteComponentFixed>(std::make_shared<SpriteComponentFixed>(s));



		//SDL_Rect Message_rect; //create a rect
		//Message_rect.x = 0;  //controls the rect's x coordinate 
		//Message_rect.y = 0; // controls the rect's y coordinte
		//Message_rect.w = 100; // controls the width of the rect
		//Message_rect.h = 100; // controls the height of the rect

		////Mind you that (0,0) is on the top left of the window/screen, think a rect as the text's box, that way it would be very simple to understance
		////Now since it's a texture, you have to put RenderCopy in your game loop area, the area where the whole code executes
		//SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

	}

private:
	TextureResource* _texture;
};

}

#endif
