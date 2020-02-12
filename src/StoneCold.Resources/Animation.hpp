
#ifndef STONECOLD_ANIMATION_H
#define STONECOLD_ANIMATION_H

#include "SDL_Base.hpp"
#include "Types.hpp"
#include <functional>
#include <string>
#include <vector>

namespace StoneCold::Resources {

enum class AnimationType { Player, NPC };

//
// Animation contains only its name and an array of source rectangles (SDL_Rect srcRects) 
// to define which part of a full Texture image is part of the Animation / should be rendered
//
struct Animation {
	Animation(const std::vector<SDL_Rect>& framePositions, uint frameTime)
		: FramePositions(framePositions), FrameCount(framePositions.size() - 1), FrameTime(frameTime) {}

	const std::vector<SDL_Rect> FramePositions;
	const size_t FrameCount;
	const uint FrameTime;
};

//
// ...
//
class AnimationResource {
public:
	AnimationResource(AnimationType type, const std::string& name, const std::unordered_map<std::string, Animation>& animations)
		: Id(std::hash<std::string>()(name)), Type(type), Name(name), Animations(animations) {}

public:
	const hash64 Id;
	const AnimationType Type;
	const std::string Name;
	const std::unordered_map<std::string, Animation>& Animations;
};

}

#endif
