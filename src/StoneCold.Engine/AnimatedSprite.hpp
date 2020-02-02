
#ifndef STONECOLD_ANIMATEDSPRITE_H
#define STONECOLD_ANIMATEDSPRITE_H

#include "Sprite.hpp"
#include "Animation.hpp"

namespace StoneCold::Engine {

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(SDL_Renderer* renderer, StoneCold::Resources::Animation* animation, SDL_Texture* texture, int width, int height, uint frameTime);

	virtual void Update(uint timestampOld, uint timestampNew) override;
	virtual void Render() override;

private:
	StoneCold::Resources::Animation* _animation;
	SDL_Rect* _currentFrame;
	const uint _frameTime;
	uint _timeElapsed;
	int _currentFrameIndex;

};

}

#endif
