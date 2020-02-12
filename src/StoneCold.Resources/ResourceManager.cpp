
#include "ResourceManager.hpp"

using namespace StoneCold::Resources;

//bool StoneCold::Resources::ResourceManager::LoadResources(const std::vector<Resource>& resources) {
//	for (const auto res : resources) {
//		if (res.Type != ResourceType::Texture)
//			continue;
//
//		LoadTexture(res);
//	}
//	return true;
//}
//
//bool StoneCold::Resources::ResourceManager::UnloadResources(const std::vector<uint>& resourceIds) {
//	return false;
//}
//
////
//// Loads a Texture form file into an SDL_Texture object
//// The returned shared_ptr will automatically call SDL_DestroyTexture on destruction
////
//void ResourceManager::LoadTexture(const Resource& resource) {
//	try {
//		// Check if the Texture was loaded already
//		if (_textures.find(resource.Id) == _textures.end()) {
//			// Load file into a SDL_Texture pointer
//			SDL_Surface* tmpSurface = IMG_Load(resource.Path.c_str());
//			auto tex = std::unique_ptr<SDL_Texture, SDL_TextureDeleter>(SDL_CreateTextureFromSurface(_renderer, tmpSurface));
//			SDL_FreeSurface(tmpSurface);
//
//			// Create and store the Texture
//			const TextureType type = TextureType::Map;
//
//			// Add the Texture to the dictionary
//			_textures.insert(std::make_pair(resource.Id, Texture(resource.Id, resource.Name, resource.Path, type, std::move(tex))));
//		}
//	}
//	catch (...) {
//		throw GameException("SDL Error on Texture creation: " + resource.Path + "\n" + std::string(SDL_GetError()));
//	}
//}
