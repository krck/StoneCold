
#ifndef STONECOLD_SETTINGS_H
#define STONECOLD_SETTINGS_H

#include <SDL.h>
#undef main

#include <SDL_image.h>
#include <SDL_ttf.h>


#define BASE_PATH				std::string("../assets/")
#define FPS						60
#define WINDOW_SIZE_WIDTH		1280
#define WINDOW_SIZE_HEIGHT		704		// 720 does not divide by 32

namespace StoneCold {

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned char byte;

}

#endif
