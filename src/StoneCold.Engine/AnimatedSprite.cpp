
#include "AnimatedSprite.hpp"

using namespace StoneCold::Engine;
using namespace StoneCold::Resources;

AnimatedSprite::AnimatedSprite(SDL_Renderer* renderer, Animation* animation, SDL_Texture* texture, int width, int height, uint frameTime)
	: Sprite(renderer, texture, width, height), _animation(animation), _frameTime(frameTime), _currentFrame(nullptr), _timeElapsed(0), _currentFrameIndex(0) { }

void AnimatedSprite::Update(uint timestampOld, uint timestampNew) {
	Sprite::Update(timestampOld, timestampNew);

	// Update the current_frame animation that should be displayed every 100 milliseconds
	this->_timeElapsed += (timestampNew - timestampOld);
	if (this->_timeElapsed > this->_frameTime) {
		this->_timeElapsed -= this->_frameTime;
		_currentFrameIndex = (_currentFrameIndex < _animation->GetAnimationFrameCount() ? _currentFrameIndex + 1 : 0);
	}
}

void AnimatedSprite::Render() {
	_currentFrame = _animation->GetAnimationFramePosition(_currentFrameIndex);

	auto flip = (velocity_X < 0 ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE);
	SDL_RenderCopyEx(_renderer, _texture, _currentFrame, &_destRect, 0, nullptr, flip);
}
