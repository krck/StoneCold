
#ifndef STONECOLD_ANIMATIONCOMPONENT_H
#define STONECOLD_ANIMATIONCOMPONENT_H

#include "SDL_Base.hpp"
#include "Entity.hpp"
#include "Component.hpp"
#include "AnimationResource.hpp"

namespace StoneCold::Engine {

//
// 2D Animation Component 
// Required: ---
// Optional: ---
//
// Takes a unordered_map of Animations and can set a current Animation based on its name
// The current Animation will be automatically updated (played) with its defined speed and
// and can be retrieved as Source rectangle by any component via GetCurrentAnimationFrame
//
class AnimationComponent : public Component {
private:
	const std::unordered_map<std::string, StoneCold::Resources::Animation>& _animations;
	const StoneCold::Resources::Animation* _currentAnimation;
	SDL_Rect _currentFrame;
	int _currentFrameIndex;
	uint _timeElapsed;

public:
	AnimationComponent(const std::unordered_map<std::string, StoneCold::Resources::Animation>& animations)
		: _animations(animations), _currentAnimation(nullptr), _currentFrame(SDL_Rect()), _currentFrameIndex(0), _timeElapsed(0) { }

	void Init(Entity* entity) override {
		Component::Init(entity);
	}

	void Update(uint frameTime) override {
		// Udpate the Animation index based on its "play-speed"
		_timeElapsed += frameTime;
		if (_timeElapsed > _currentAnimation->FrameTime) {
			_timeElapsed -= _currentAnimation->FrameTime;
			_currentFrameIndex = (_currentFrameIndex < _currentAnimation->FrameCount ? _currentFrameIndex + 1 : 0);
		}
	}

	void SetCurrentAnimation(const std::string& name) {
		// Play a different Animation, based on its name
		_currentAnimation = &_animations.find(name)->second;
		if (_currentFrameIndex > _currentAnimation->FrameCount)
			_currentFrameIndex = 0;
	}

	SDL_Rect GetCurrentAnimationFrame() {
		// Get the Source rectange (frame inside the texture) based on the current index
		return _currentAnimation->FramePositions[_currentFrameIndex];
	}
};

}

#endif