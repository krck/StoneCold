
#ifndef STONECOLD_COMPONENTS_H
#define STONECOLD_COMPONENTS_H

#include "SDL_Base.hpp"
#include "Types.hpp"
#include "Vec2.hpp"
#include "AnimationResource.hpp"
#include <vector>

namespace StoneCold::Engine {

using namespace StoneCold::Base;
using namespace StoneCold::Resources;

const mask COMP_MASK_ANIMATION = 0x0000000000000001;
const mask COMP_MASK_UI_ATTRIBUTE = 0x0000000000000002;
const mask COMP_MASK_COLLISION = 0x0000000000000004;
const mask COMP_MASK_KEYBOARD = 0x0000000000000008;
const mask COMP_MASK_SPRITE = 0x0000000000000010;
const mask COMP_MASK_SPRITE_LAYERED = 0x0000000000000020;
const mask COMP_MASK_TRANSFORMATION = 0x0000000000000040;
const mask COMP_MASK_VELOCITY = 0x0000000000000080;
const mask COMP_MASK_POSITION = 0x0000000000000100;
const mask COMP_MASK_POSITION_LAYERED = 0x0000000000000200;

struct AnimationComponent_x {
	const std::unordered_map<std::string, Animation>* Animations;
	Animation* CurrentAnimation;
	uint32 CurrentFrameIndex;
	uint32 TimeElapsed;
};

struct AttributeComponentUI_x {
	UiElementAttribute UiAttribute;
};

struct CollisionComponent_x {
	const std::string Tag;	// USE ENUM TYPE
	const Vec2 Hitbox;
	SDL_FRect CollisionBox;
	CollisionComponent_x* CollisionWith;
	const bool IsFixed;		// REMOVE
};

struct KeyboardComponent_x {
	const std::vector<uint8>& KeyStates;	// FIXED use array?
};

struct SpriteComponent_x {
	SDL_Texture* Texture;
	SDL_RendererFlip Flip;
};

struct SpriteLayeredComponent_x {
	SDL_Texture* TextureBottom;
	SDL_RendererFlip FlipBottom;
	SDL_Texture* TextureTop;
	SDL_RendererFlip FlipTop;
};

struct TransformationComponent_x {
	Vec2 Position;
	uint32 BaseSpeed;
	uint32 Speed;
	float Scale;
};

struct VelocityComponent_x {
	Vec2 Velocity;
};

struct ScreenPositionComponent {
	SDL_Rect SrcRect;
	SDL_FRect DestRect;

};

struct ScreenPositionLayeredComponent {
	SDL_Rect SrcRectBottom;
	SDL_FRect DestRectBottom;
	SDL_Rect SrcRectTop;
	SDL_FRect DestRectTop;

};

}

#endif
