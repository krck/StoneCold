
#ifndef STONECOLD_MOTIONRENDERSYSTEM_H
#define STONECOLD_MOTIONRENDERSYSTEM_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentArray.hpp"

namespace StoneCold::Engine {

class MotionRenderSystem : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a RENDER_MOTION Flag, a ScreenPosition and a Sprite Component will be rendered with this System
	//
	MotionRenderSystem(SDL_Renderer* renderer, EntityComponentArray<ScreenPositionComponent>& position, 
					   EntityComponentArray<VelocityComponent>& velocity, EntityComponentArray<SpriteComponent>& sprite)
		: System((RENDER_MOTION | GetComponentMask<ScreenPositionComponent>() | GetComponentMask<VelocityComponent>() | GetComponentMask<SpriteComponent>()))
		, _renderer(renderer), _positionComponents(position), _velocityComponents(velocity), _spriteComponents(sprite) { }

	MotionRenderSystem(const MotionRenderSystem&) = delete;
	MotionRenderSystem& operator=(const MotionRenderSystem&) = delete;

	virtual void Render(SDL_FRect camera) override {
		for (const auto& entityId : _entities) {
			auto& p = _positionComponents[entityId];
			auto& v = _velocityComponents[entityId];
			auto& s = _spriteComponents[entityId];

			// Get the Destination rectangle (render position on screen) relative to the camera (as int)
			SDL_FRect currentDest = {
				floorf(p.DestRect.x - camera.x),
				floorf(p.DestRect.y - camera.y),
				floorf(p.DestRect.w),
				floorf(p.DestRect.h)
			};

			// Flip the sprite based on the current velocity
			s.Flip = (v.Velocity.X == 0 ? s.Flip : (v.Velocity.X < 0 ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE));

			// Add Sprite to the SDL Renderer
			SDL_RenderCopyExF(_renderer, s.Texture, &p.SrcRect, &currentDest, 0, nullptr, s.Flip);
		}
	}

private:
	SDL_Renderer* _renderer;
	EntityComponentArray<ScreenPositionComponent>& _positionComponents;
	EntityComponentArray<VelocityComponent>& _velocityComponents;
	EntityComponentArray<SpriteComponent>& _spriteComponents;
};

}

#endif
