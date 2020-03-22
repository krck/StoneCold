
#ifndef STONECOLD_COMPONENTS_H
#define STONECOLD_COMPONENTS_H

#include "SDL_Base.hpp"
#include "Types.hpp"
#include "Vec2.hpp"
#include "AnimationResource.hpp"
#include <unordered_map>
#include <vector>

namespace StoneCold::Engine {

using namespace StoneCold::Base;
using namespace StoneCold::Resources;

struct AnimationComponent {
	const std::unordered_map<std::string, Animation>* Animations;
	Animation* CurrentAnimation;
	uint32 CurrentFrameIndex;
	uint32 TimeElapsed;
};

struct AttributeComponentUI {
	UiElementAttribute UiAttribute;
};

struct CollisionComponent {
	std::string Tag;	// USE ENUM TYPE
	Vec2 Hitbox;
	SDL_FRect CollisionBox;
	CollisionComponent* CollisionWith;
	bool IsFixed;		// REMOVE
};

struct KeyboardComponent {
	const std::vector<uint8>* KeyStates;	// FIXED use array?
};

struct SpriteComponent {
	SDL_Texture* Texture;
	SDL_RendererFlip Flip;
};

struct SpriteLayeredComponent {
	SDL_Texture* TextureBottom;
	SDL_RendererFlip FlipBottom;
	SDL_Texture* TextureTop;
	SDL_RendererFlip FlipTop;
};

struct TransformationComponent {
	Vec2 Position;
	Vec2 Dimension;
	uint32 BaseSpeed;
	uint32 Speed;
	uint32 Scale;
};

struct VelocityComponent {
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

//
// Component (Bit-)Masks
//
static auto ComponentMasks = std::unordered_map<hash, const mask>({
	{ GetTypeHash<AnimationComponent>(),				0x0000000000000001 },
	{ GetTypeHash<AttributeComponentUI>(),				0x0000000000000002 },
	{ GetTypeHash<CollisionComponent>(),				0x0000000000000004 },
	{ GetTypeHash<KeyboardComponent>(),					0x0000000000000008 },
	{ GetTypeHash<SpriteComponent>(),					0x0000000000000010 },
	{ GetTypeHash<SpriteLayeredComponent>(),			0x0000000000000020 },
	{ GetTypeHash<TransformationComponent>(),			0x0000000000000040 },
	{ GetTypeHash<VelocityComponent>(),					0x0000000000000080 },
	{ GetTypeHash<ScreenPositionComponent>(),			0x0000000000000100 },
	{ GetTypeHash<ScreenPositionLayeredComponent>(),	0x0000000000000200 }
	});

}

#endif
