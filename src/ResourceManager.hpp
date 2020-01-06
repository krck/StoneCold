
#ifndef STONECOLD_RESOURCEMANAGER_H
#define STONECOLD_RESOURCEMANAGER_H

#include "Settings.hpp"
#include "Exception.hpp"
#include <windows.h>
#include <memory>
#include <string>
#include <map>

namespace StoneCold {

class ResourceManager {
public:
	ResourceManager() : _textures(std::map<std::string, std::shared_ptr<SDL_Texture>>()) { }
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	std::shared_ptr<SDL_Texture> LoadTexture(SDL_Renderer* renderer, const std::string& fileName);

private:
	std::map<std::string, std::shared_ptr<SDL_Texture>> _textures;

};

}

#endif
