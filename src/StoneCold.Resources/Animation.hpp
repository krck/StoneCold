
#ifndef STONECOLD_ANIMATION_H
#define STONECOLD_ANIMATION_H

#include "SDL_Base.hpp"
#include "Types.hpp"
#include <string>
#include <vector>

namespace StoneCold::Resources {

class Animation {
public:
	Animation(const std::string& name, const std::vector<SDL_Rect>& framePositions)
		: _animationName(name), _animationFramePositions(framePositions) { }

	Animation(std::string&& name, std::vector<SDL_Rect>&& framePositions)
		: _animationName(std::move(name)), _animationFramePositions(std::move(framePositions)) { }


	size_t GetAnimationFrameCount() const { return _animationFramePositions.size() - 1; }

	SDL_Rect* GetAnimationFramePosition(uint index) { return &_animationFramePositions[index]; }

private:
	std::string _animationName;
	std::vector<SDL_Rect> _animationFramePositions;
};

}

#endif
