
#include "TextureManager.hpp"

using namespace StoneCold;

//
// Loads a Texture form file into an SDL_Texture object
// The returned shared_ptr will automatically call SDL_DestroyTexture on destruction
//
std::shared_ptr<SDL_Texture> TextureManager::LoadTexture(SDL_Renderer* renderer, const std::string& fileName) {
	try {
		SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());
		auto tex = sdl_make_shared<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, tmpSurface));
		SDL_FreeSurface(tmpSurface);
		return tex;
	}
	catch (...) {
		throw GameException("SDL Error on Texture creation: " + fileName + "\n" + std::string(SDL_GetError()));
	}
}

void TextureManager::Draw(SDL_Renderer* renderer, SDL_Texture* tex, const SDL_Rect& src, const SDL_Rect& dest, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(renderer, tex, &src, &dest, NULL, NULL, flip);
}
