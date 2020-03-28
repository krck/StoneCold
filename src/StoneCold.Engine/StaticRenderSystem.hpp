
#ifndef STONECOLD_STATICRENDERSYSTEM_H
#define STONECOLD_STATICRENDERSYSTEM_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentArray.hpp"

namespace StoneCold::Engine {

class StaticRenderSystem : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a RENDER_STATIC Flag, a ScreenPosition and a Sprite Component will be rendered with this System
	//
	StaticRenderSystem(SDL_Renderer* renderer, EntityComponentArray<ScreenPositionComponent>& position, EntityComponentArray<SpriteComponent>& sprite)
		: System((RENDER_STATIC | GetComponentMask<ScreenPositionComponent>() | GetComponentMask<SpriteComponent>()))
		, _renderer(renderer), _positionComponents(position), _spriteComponents(sprite) { }

	StaticRenderSystem(const StaticRenderSystem&) = delete;
	StaticRenderSystem& operator=(const StaticRenderSystem&) = delete;

	virtual void Render(SDL_FRect camera) override {
		for (const auto& entityId : _entities) {
			auto& p = _positionComponents[entityId];
			auto& s = _spriteComponents[entityId];

			// Get the Destination rectangle (render position on screen) relative to the camera (as int)
			SDL_FRect currentDest = {
				floorf(p.DestRect.x - camera.x),
				floorf(p.DestRect.y - camera.y),
				floorf(p.DestRect.w),
				floorf(p.DestRect.h)
			};

			// Add Sprite to the SDL Renderer
			SDL_RenderCopyExF(_renderer, s.Texture, &p.SrcRect, &currentDest, 0, nullptr, s.Flip);
		}
	}

private:
	SDL_Renderer* _renderer;
	EntityComponentArray<ScreenPositionComponent>& _positionComponents;
	EntityComponentArray<SpriteComponent>& _spriteComponents;
};

}

#endif
