
#ifndef STONECOLD_MAP_H
#define STONECOLD_MAP_H

#include "SDL_Base.hpp"

namespace StoneCold::Engine {

class Map {
public:
	Map();
	Map(const Map&) = delete;
	Map& operator=(const Map&) = delete;

	void LoadMap();
	void RenderMap();

	~Map();

private:
	SDL_Rect _src, _dest;
	SDL_Texture* _dirt;
	SDL_Texture* _grass;
	SDL_Texture* _water;

	int map[20][25];

};

}

#endif
