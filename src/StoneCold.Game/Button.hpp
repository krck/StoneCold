
#ifndef STONECOLD_BUTTON_H
#define STONECOLD_BUTTON_H

#include "Entity.hpp"
#include "TextureResource.hpp"
#include "AnimationResource.hpp"
#include "CollisionComponent.hpp"
#include "SpriteComponentGui.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

class Button : public Entity {
public:
	Button(SDL_Renderer* renderer, TextureResource* buttonTexture, TextureResource* contentTexture, AnimationResource* animation, SDL_FRect destRect, Vec2 contentSize) {
		_buttonTexture = buttonTexture;
		_contentTexture = contentTexture;
		_animation = animation;

		// Set the Source and Destination of the Content. Dest: Content is always centered within the Button
		SDL_Rect contentSrc = { 0, 0, static_cast<int>(contentSize.X), static_cast<int>(contentSize.Y) };
		auto centerBtn = Vec2(destRect.x + (destRect.w / 2.f), destRect.y + (destRect.h / 2.f));
		SDL_FRect contentDest = { centerBtn.X - (contentSize.X / 2.f), centerBtn.Y - (contentSize.Y / 2.f), contentSize.X, contentSize.Y };

		// Add the Button Components (Trans, Moving and Animation are the construct for switching Hover/Non-Hover
		// The SpriteComponentFixed is used to display the content (Text, Image, ...) within the Button 
		auto c = CollisionComponent("button", true, Vec2(destRect.w, destRect.h), destRect);
		auto a = AnimationComponent(_animation->Animations, false);
		auto s = SpriteComponentGui(renderer, buttonTexture->GetTextureSDL(), contentTexture->GetTextureSDL(), SDL_Rect(), destRect, contentSrc, contentDest);

		// Set a default Animation
		a.SetCurrentAnimation("not_hover");

		// Add the Components. The order is important!
		AddComponent<CollisionComponent>(std::make_shared<CollisionComponent>(c));
		AddComponent<AnimationComponent>(std::make_shared<AnimationComponent>(a));
		AddComponent<SpriteComponentGui>(std::make_shared<SpriteComponentGui>(s));
	}

private:
	TextureResource* _buttonTexture;
	TextureResource* _contentTexture;
	AnimationResource* _animation;
};

}

#endif
