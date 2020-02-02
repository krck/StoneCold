
#ifndef STONECOLD_SPRITE_H
#define STONECOLD_SPRITE_H

#include "Entity.hpp"
#include <string>

namespace StoneCold::Engine {

class Sprite : public Entity {
public:
	Sprite(SDL_Renderer* renderer, SDL_Texture* texture, int width, int height);

	virtual void Update(uint timestampOld, uint timestampNew) override;
	virtual void Render() override;

	int velocity_X, velocity_Y;

protected:
	SDL_Texture* _texture;
	const int _width, _height;
	// Rectangles to specify the source (inside the texture) and the destination (on the screen)
	SDL_Rect _srcRect, _destRect;

};

}

#endif
