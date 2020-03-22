
#ifndef STONECOLD_RENDERSYSTEM_H
#define STONECOLD_RENDERSYSTEM_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentArray.hpp"

namespace StoneCold::Engine {

class RenderSystem : public System {
public:
	RenderSystem(mask componentMask, SDL_Renderer* renderer, EntityComponentArray<ScreenPositionComponent>& position, EntityComponentArray<SpriteComponent>& sprite)
		: System(componentMask), _renderer(renderer), _positionComponents(position), _spriteComponents(sprite) { }

	RenderSystem(const RenderSystem&) = delete;
	RenderSystem& operator=(const RenderSystem&) = delete;

	virtual void Render(SDL_FRect camera) override {
		for (const auto& entityId : _entities) {
			auto& pos = _positionComponents[entityId];
			auto& spr = _spriteComponents[entityId];

			// Get the Destination rectangle (render position on screen) relative to the camera (as int)
			SDL_FRect currentDest = {
				floorf(pos.DestRect.x - camera.x),
				floorf(pos.DestRect.y - camera.y),
				floorf(pos.DestRect.w),
				floorf(pos.DestRect.h)
			};

			// Add Sprite to the SDL Renderer
			SDL_RenderCopyExF(_renderer, spr.Texture, &pos.SrcRect, &currentDest, 0, nullptr, spr.Flip);
		}
	}

private:
	SDL_Renderer* _renderer;
	EntityComponentArray<ScreenPositionComponent>& _positionComponents;
	EntityComponentArray<SpriteComponent>& _spriteComponents;
};

}

#endif
