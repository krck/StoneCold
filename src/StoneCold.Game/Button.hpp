
#ifndef STONECOLD_BUTTON_H
#define STONECOLD_BUTTON_H

#include "Entity.hpp"
#include "TextureResource.hpp"
#include "AnimationResource.hpp"

namespace StoneCold::Game {

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

class Button : public Entity {
public:
	Button(EntityComponentSystem* ecs, TextureResource* buttonTex, TextureResource* contentTex, AnimationResource* animation, SDL_FRect destRect, Vec2i contentSize)
		: Entity(ecs), _buttonTexture(buttonTex), _contentTexture(contentTex), _animation(animation) {

		// Set the Source and Destination of the Content. Dest: Content is always centered within the Button
		SDL_Rect contentSrc = { 0, 0, static_cast<int>(contentSize.X), static_cast<int>(contentSize.Y) };
		auto centerBtn = Vec2(destRect.x + (destRect.w / 2.f), destRect.y + (destRect.h / 2.f) - 4.f);
		SDL_FRect contentDest = { centerBtn.X - (contentSize.X / 2.f), centerBtn.Y - (contentSize.Y / 2.f), static_cast<float>(contentSize.X), static_cast<float>(contentSize.Y) };

		// Set a default Animation
		//a.SetCurrentAnimation("idle");

		// Add the Button Components (Trans, Moving and Animation are the construct for switching Hover/Non-Hover
		// The SpriteComponentFixed is used to display the content (Text, Image, ...) within the Button 
		auto flip = SDL_RendererFlip::SDL_FLIP_NONE;
		AddComponent<CollisionComponent>({ 3, Vec2(destRect.w, destRect.h), destRect, nullptr });
		AddComponent<AnimationComponent>({ _animation->Animations, nullptr, 0 });
		AddComponent<ScreenPositionLayeredComponent>({ SDL_Rect(), destRect, contentSrc, contentDest });
		AddComponent<SpriteLayeredComponent>({ buttonTex->GetTextureSDL(), flip, contentTex->GetTextureSDL(), flip });
	}

private:
	TextureResource* _buttonTexture;
	TextureResource* _contentTexture;
	AnimationResource* _animation;
};

}

#endif
