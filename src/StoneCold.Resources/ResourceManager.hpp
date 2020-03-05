
#ifndef STONECOLD_RESOURCEMANAGER_H
#define STONECOLD_RESOURCEMANAGER_H

#include <windows.h>
#include "Settings.hpp"
#include "Exception.hpp"
#include "Data_Animations.hpp"
#include "Data_Textures.hpp"
#include "AnimationResource.hpp"
#include "TextureResource.hpp"
#include "FontResource.hpp"
#include <unordered_map>
#include <algorithm>
#include <memory>

namespace StoneCold::Resources {

//
// ResorceManager 
// - Ensures that only one copy of each unique resource exists
// - Manages the lifetime of each resource (loading / unloading)
// - !NOT YET! Handles loading of composite resources (resource dependencies)
//
class ResourceManager {
public:
	ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	bool Initialize(SDL_Renderer* renderer);

	//
	// Load any Resource based on its Type
	// Ensures that Resources are loaded only once
	//
	template<typename T>
	T* LoadResource(ResourceLifeTime resourceLifeTime, const std::string& name);

	//
	// Load a specific Texture Resource based on a Font, Text and FontColor
	// Ensures that Resources are loaded only once
	//
	TextureResource* LoadFontTexture(ResourceLifeTime rlt, const std::string& name, TTF_Font* font, const std::string& text, const SDL_Color& color);

	//
	// Unload (cleanup) all Resources of a specific LifeTime
	//
	void UnloadResources(ResourceLifeTime resourceLifeTime);

	template<typename T>
	inline T* GetResource(const std::string& name) { return static_cast<T*>(_resources[name].get()); }

	inline bool IsResourceLoaded(const std::string& name) const { return (_resources.find(name) != _resources.end()); }

	~ResourceManager() = default;

private:
	TextureResource CreateTexture(const std::string& name);
	AnimationResource CreateAnimation(const std::string& name);
	FontResource CreateFont(const std::string& name);

private:
	std::string _basePath;
	std::unordered_map<std::string, std::shared_ptr<Resource>> _resources;
	std::unordered_map<ResourceLifeTime, std::vector<std::string>> _resouceLifetimes;
	SDL_Renderer* _renderer;
};

}

#endif
