
#ifndef STONECOLD_TEXTUREMANAGER_H
#define STONECOLD_TEXTUREMANAGER_H

#include "Settings.hpp"
#include "Exception.hpp"
#include <windows.h>
#include <memory>
#include <string>

namespace StoneCold {

class TextureManager {
public:
	static std::shared_ptr<SDL_Texture> LoadTexture(SDL_Renderer* renderer, const std::string& fileName);
	static void Draw(SDL_Renderer* renderer, SDL_Texture* tex, const SDL_Rect& src, const SDL_Rect& dest, SDL_RendererFlip flip);
};

// Custom Deleter called on shared_ptr destruction to cleanup the SDL Texture 
static void SDL_Deleter(SDL_Texture* p) { if (p != nullptr) SDL_DestroyTexture(p); }

// SDL and KiwiGUI Shared Pointer creation functions globally in the Fourier namespace
template <typename T>
std::shared_ptr<T> sdl_make_shared(T* t) { return std::shared_ptr<T>(t, [](T* t) { SDL_Deleter(t); }); }

}

#endif
