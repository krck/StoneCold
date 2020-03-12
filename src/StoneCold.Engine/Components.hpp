
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

// COMPONENT Examples:
// - Position(x, y)
// - Velocity(x, y)
// - Physics(body)
// - Sprite(images, animations)
// - Health(value)
// - Character(name, level)
// - Player(empty)

// ENTITY Examples:
// - Rock(Position, Sprite)
// - Crate(Position, Sprite, Health)
// - Sign(Position, Sprite, Text)
// - Ball(Position, Velocity, Physics, Sprite)
// - Enemy(Position, Velocity, Sprite, Character, Input, AI)
// - Player(Position, Velocity, Sprite, Character, Input, Player)

// SYSTEM Examples:
// - Movement(Position, Velocity) - Adds velocity to position
// - Gravity(Velocity) - Accelerates velocity due to gravity
// - Render(Position, Sprite) - Draws sprites
// - PlayerControl(Input, Player) - Sets the player - controlled entity's input according to a controller
// - BotControl(Input, AI) - Sets a bot - controlled entity's input according to an AI agent



const mask COMP_MASK_ANIMATION = 0x0000000000000001;
const mask COMP_MASK_UI_ATTRIB = 0x0000000000000002;
const mask COMP_MASK_COLLISION = 0x0000000000000004;
const mask COMP_MASK_KEYBOARD_ = 0x0000000000000008;
const mask COMP_MASK_SPRITE___ = 0x0000000000000010;
const mask COMP_MASK_SPRITE_LY = 0x0000000000000020;
const mask COMP_MASK_TRANSFORM = 0x0000000000000040;
const mask COMP_MASK_VELOCITY_ = 0x0000000000000080;
const mask COMP_MASK_POSITION_ = 0x0000000000000100;
const mask COMP_MASK_POS_LAYER = 0x0000000000000200;

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
	const uint32 BaseSpeed;
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
