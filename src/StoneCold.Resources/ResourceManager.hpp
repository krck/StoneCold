
#ifndef STONECOLD_RESOURCEMANAGER_H
#define STONECOLD_RESOURCEMANAGER_H

#include "Exception.hpp"
#include "Data_Animations.hpp"
#include "Data_Textures.hpp"
#include "AnimationResource.hpp"
#include "TextureResource.hpp"
#include "FontResource.hpp"
#include <windows.h>
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
	// Load the specific Resource based on Type
	// Ensures that any Resource is loaded only once, per LifeTime
	//
	template<typename T>
	void LoadResource(ResourceLifeTime resourceLifeTime, const std::string& name) {
		// Load each ressource only once
		if (!IsResourceLoaded(name)) {
			// Create the specific Resource based on Type
			if (std::is_same<T, TextureResource>::value) {
				_resources.insert({ name, std::make_shared<TextureResource>(CreateTexture(name)) });
				_resouceLifetimes[resourceLifeTime].push_back(name);
			}
			else if (std::is_same<T, AnimationResource>::value) {
				_resources.insert({ name, std::make_shared<AnimationResource>(CreateAnimation(name)) });
				_resouceLifetimes[resourceLifeTime].push_back(name);
			}
			else if (std::is_same<T, FontResource>::value) {

			}
		}
	}

	//
	// Reset a specific Resource Map (LifeTime storage) completely
	//
	void UnloadResources(ResourceLifeTime resourceLifeTime);

	template<typename T>
	inline T* GetResource(const std::string& name) { return static_cast<T*>(_resources[name].get()); }

	inline bool IsResourceLoaded(const std::string& name) const { return (_resources.find(name) != _resources.end()); }

	~ResourceManager() = default;

private:
	//
	// Loads a Texture form file into an SDL_Texture object
	// The returned shared_ptr will automatically call SDL_DestroyTexture on destruction
	//
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
