
#ifndef STONECOLD_ANIMATEDSPRITE_H
#define STONECOLD_ANIMATEDSPRITE_H

#include "Sprite.hpp"
#include "Animation.hpp"

namespace StoneCold {

class AnimatedSprite : public Sprite {
public:
	AnimatedSprite(SDL_Renderer* renderer, Animation* animation, SDL_Texture* texture, int width, int height, uint frameTime);

	virtual void Update(uint timestampOld, uint timestampNew) override;
	virtual void Render() override;

private:
	Animation* _animation;
	SDL_Rect* _currentFrame;
	const uint _frameTime;
	uint _timeElapsed;
	int _currentFrameIndex;

};

}

#endif
