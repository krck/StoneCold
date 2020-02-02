
#include "TextureManager.hpp"

using namespace StoneCold::Resources;

//
// Loads a Texture form file into an SDL_Texture object
// The returned shared_ptr will automatically call SDL_DestroyTexture on destruction
//
void TextureManager::LoadTexture(SDL_Renderer* renderer, const std::string& fileName) {
	try {
		// Check if the Texture was loaded already
		if (!std::any_of(_textures.begin(), _textures.end(), [fileName](Texture t) { return t.TexturePath == fileName; })) {
			// Load file into a SDL_Texture pointer
			SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());
			auto tex = std::unique_ptr<SDL_Texture, SDL_TextureDeleter>(SDL_CreateTextureFromSurface(renderer, tmpSurface));
			SDL_FreeSurface(tmpSurface);

			// Create and store the Texture
			const std::string name = "Texture";
			const TextureType type = TextureType::Map;

			_textures.push_back(Texture(name, fileName, type, std::move(tex)));
		}
	}
	catch (...) {
		throw GameException("SDL Error on Texture creation: " + fileName + "\n" + std::string(SDL_GetError()));
	}
}
