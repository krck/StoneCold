
#include "ResourceManager.hpp"

using namespace StoneCold::Resources;

ResourceManager::ResourceManager()
	: _resources(std::unordered_map<std::string, std::shared_ptr<Resource>>())
	, _resouceLifetimes(std::unordered_map<ResourceLifeTime, std::vector<std::string>>())
	, _renderer(nullptr) {}

bool ResourceManager::Initialize(SDL_Renderer* renderer) {
	if (renderer != nullptr) {
		_renderer = renderer;

		_resouceLifetimes.insert({ ResourceLifeTime::Global, std::vector<std::string>() });
		_resouceLifetimes.insert({ ResourceLifeTime::Level, std::vector<std::string>() });
		_resouceLifetimes.insert({ ResourceLifeTime::Sequence, std::vector<std::string>() });

		return true;
	}
	else {
		return false;
	}
}

void ResourceManager::UnloadResources(ResourceLifeTime resourceLifeTime) {
	// Remove all Resources that are mapped to the specific lifetime
	const auto& keys = _resouceLifetimes[resourceLifeTime];
	for (const auto& key : keys) {
		_resources.erase(key);
	}

	// Clear all ResourceLifeTime keys
	_resouceLifetimes[resourceLifeTime] = std::vector<std::string>();
}

TextureResource ResourceManager::CreateTexture(const std::string& name) {
	try {
		// Load file into a SDL_Texture pointer
		SDL_Surface* tmpSurface = IMG_Load(name.c_str());
		auto tex = std::unique_ptr<SDL_Texture, SDL_TextureDeleter>(SDL_CreateTextureFromSurface(_renderer, tmpSurface));
		SDL_FreeSurface(tmpSurface);

		// Create the TextureResource
		return TextureResource(name, std::move(tex));
	}
	catch (...) {
		throw GameException("SDL Error on Texture creation: " + name + "\n" + std::string(SDL_GetError()));
	}
}

AnimationResource ResourceManager::CreateAnimation(const std::string& name) {
	try {
		return AnimationResource(name, AnimationData.find(name)->second);
	}
	catch (...) {
		throw GameException("Error on Animation creation: " + name);

	}
}

FontResource ResourceManager::CreateFont(const std::string& name) {
	return FontResource(name);
}
