
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

}

#endif
