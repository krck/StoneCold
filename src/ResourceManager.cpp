
#include "ResourceManager.hpp"

using namespace StoneCold;

//
// Loads a Texture form file into an SDL_Texture object
// The returned shared_ptr will automatically call SDL_DestroyTexture on destruction
//
std::shared_ptr<SDL_Texture> ResourceManager::LoadTexture(SDL_Renderer* renderer, const std::string& fileName) {
	try {
		// Check if the Texture was loaded already
		if (_textures.find(fileName) == _textures.end()) {
			SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());
			auto tex = sdl_make_shared<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, tmpSurface));
			SDL_FreeSurface(tmpSurface);

			_textures[fileName] = tex;
		}
		
		return _textures[fileName];
	}
	catch (...) {
		throw GameException("SDL Error on Texture creation: " + fileName + "\n" + std::string(SDL_GetError()));
	}
}
