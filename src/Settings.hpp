
#ifndef STONECOLD_SETTINGS_H
#define STONECOLD_SETTINGS_H

#include <SDL.h>
#undef main

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>

#define BASE_PATH			std::string("../assets/")
#define FPS					60
#define WINDOW_SIZE_WIDTH	1280
#define WINDOW_SIZE_HEIGHT	720		// 720 does not divide by 32

namespace StoneCold {

typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned char		byte;

// Custom deleter functions (static for shared or struct for unique pointers) to cleanup the SDL Resources 
struct SDL_WindowDeleter { void operator()(SDL_Window* p) { if (p != nullptr) SDL_DestroyWindow(p); } };
struct SDL_RendererDeleter { void operator()(SDL_Renderer* p) { if (p != nullptr) SDL_DestroyRenderer(p); } };
static void SDL_Deleter(SDL_Texture* p) { if (p != nullptr) SDL_DestroyTexture(p); }

template <typename T>
std::shared_ptr<T> sdl_make_shared(T* t) { return std::shared_ptr<T>(t, [](T* t) { SDL_Deleter(t); }); }

}

#endif
