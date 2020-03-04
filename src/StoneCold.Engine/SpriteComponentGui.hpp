
#ifndef STONECOLD_SPRITECOMPONENTGUI_H
#define STONECOLD_SPRITECOMPONENTGUI_H

#include "SDL_Base.hpp"
#include "Entity.hpp"
#include "Component.hpp"
#include "AnimationComponent.hpp"

namespace StoneCold::Engine {

//
// 2D fixed GUI Sprite Component (Button, CheckBox, ...)
// Required: ---
// Optional: AnimationComponent
//
// Contains information needed to render a 2D GUI Sprite (Texture, SDL_Renderer, ...)
// It has two SDL_Textures. One in the Background and one with some Widget Content (Text, Icon)
// The GUI Component can also have a Animation Background to switch between hover/not-hover, checked/not-checked
//
class SpriteComponentGui : public Component {
private:
	AnimationComponent* _animationComponent;
	SDL_Renderer* _renderer;
	SDL_Texture* _background;
	SDL_Texture* _content;
	SDL_Rect _backSrc;
	const SDL_Rect _contSrc;
	const SDL_FRect _backDest;
	const SDL_FRect _contDest;

public:
	SpriteComponentGui(SDL_Renderer* renderer, SDL_Texture* background, SDL_Texture* content, SDL_Rect backSrc, SDL_FRect backDest, SDL_Rect contSrc, SDL_FRect contDest)
		: _renderer(renderer), _background(background), _content(content), _animationComponent(nullptr)
		, _backSrc(backSrc), _backDest(backDest), _contSrc(contSrc), _contDest(contDest) { }

	void Init(Entity* entity) override {
		Component::Init(entity);

		// Get the AnimationComponent (if it has one) to get the current framePosition, aka. _srcRect
		if (_entity->HasComponent<AnimationComponent>())
			_animationComponent = _entity->GetComponent<AnimationComponent>();
	}

	void Render(SDL_FRect camera) override {
		// If the Sprite Background is Animated, get the current Source rectangle (frame inside the texture) based on the Animation
		if (_animationComponent != nullptr) {
			_backSrc = _animationComponent->GetCurrentAnimationFrame();
		}

		// Add Sprite to the SDL Renderer
		SDL_RenderCopyF(_renderer, _background, &_backSrc, &_backDest);
		SDL_RenderCopyF(_renderer, _content, &_contSrc, &_contDest);
	}
};

}

#endif
