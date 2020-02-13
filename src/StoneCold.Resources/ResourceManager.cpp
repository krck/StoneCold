
#include "ResourceManager.hpp"

using namespace StoneCold::Resources;

ResourceManager::ResourceManager()
	: _globalResources(std::unordered_map<std::string, std::unique_ptr<Resource>>())
	, _levelResources(std::unordered_map<std::string, std::unique_ptr<Resource>>())
	, _sequenceResources(std::unordered_map<std::string, std::unique_ptr<Resource>>())
	, _renderer(nullptr) {}

bool ResourceManager::Initialize(SDL_Renderer* renderer) {
	_renderer = renderer;
}

template<typename T>
inline bool ResourceManager::LoadResource(ResourceLifeTime resourceLifeTime, const std::string& name) {
	auto& resMap = GetResourceMap(resourceLifeTime);

	// Check if the 
	if (std::is_same<T, TextureResource>::value) {

	}
	else if (std::is_same<T, AnimationResource>::value) {

	}
	else if (std::is_same<T, FontResource>::value) {

	}

	// check IsResourceLoaded<T>() is in the dictionary already
	// if not ... load the specific Resource based on Type
	// by calling the private Function
	return false;
}

bool ResourceManager::UnloadResources(ResourceLifeTime resourceLifeTime) {
	// Clear the wohle dictionary based on Type
	return false;
}

template<typename T>
T* StoneCold::Resources::ResourceManager::GetResource(ResourceLifeTime resourceLifeTime, const std::string& name) {
	auto& resMap = GetResourceMap(resourceLifeTime);
	return static_cast<T*>(resMap[name].get());
}

bool StoneCold::Resources::ResourceManager::IsResourceLoaded(ResourceLifeTime resourceLifeTime, const std::string& name) {
	auto& resMap = GetResourceMap(resourceLifeTime);
	return (resMap.find(name) != resMap.end());
}

std::unordered_map<std::string, std::unique_ptr<Resource>>& StoneCold::Resources::ResourceManager::GetResourceMap(ResourceLifeTime resourceLifeTime) {
	// Get a reference to the correct Resource Map based on type ResourceLifeTime
	return (resourceLifeTime == ResourceLifeTime::Global) ? _globalResources :
		(resourceLifeTime == ResourceLifeTime::Level) ? _levelResources :
		_sequenceResources;
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
	return AnimationResource();
}

FontResource ResourceManager::CreateFont(const std::string& name) {
	return FontResource();
}
