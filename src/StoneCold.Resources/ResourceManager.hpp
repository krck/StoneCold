
#ifndef STONECOLD_RESOURCEMANAGER_H
#define STONECOLD_RESOURCEMANAGER_H

#include "Exception.hpp"
#include "AnimationResource.hpp"
#include "TextureResource.hpp"
#include "FontResource.hpp"
#include <unordered_map>
#include <algorithm>
#include <memory>

namespace StoneCold::Resources {

//
// ResourceLifeTimes
// - Global: Resource is needed as the game is running (Player Character, GUI Elements, Fonts, Music, ...)
// - Level: Resource is only needed during a specific Level (Ground-Textures, NPC Animations, ...)
// - Sequence: Resource is only for a very short duration like a Cutscene
//
enum class ResourceLifeTime { Global, Level, Sequence };

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
	bool LoadResource(ResourceLifeTime resourceLifeTime, const std::string& name);

	//
	// Reset a specific Resource Map (LifeTime storage) completely
	//
	bool UnloadResources(ResourceLifeTime resourceLifeTime);

	template<typename T>
	T* GetResource(ResourceLifeTime resourceLifeTime, const std::string& name);

	bool IsResourceLoaded(ResourceLifeTime resourceLifeTime, const std::string& name);

	~ResourceManager() = default;

private:
	std::unordered_map<std::string, std::unique_ptr<Resource>>& GetResourceMap(ResourceLifeTime resourceLifeTime);

	//
	// Loads a Texture form file into an SDL_Texture object
	// The returned shared_ptr will automatically call SDL_DestroyTexture on destruction
	//
	TextureResource CreateTexture(const std::string& name);
	AnimationResource CreateAnimation(const std::string& name);
	FontResource CreateFont(const std::string& name);
	
private:
	// All Resources exist only once with a managed lifetime
	std::unordered_map<std::string, std::unique_ptr<Resource>> _globalResources;
	std::unordered_map<std::string, std::unique_ptr<Resource>> _levelResources;
	std::unordered_map<std::string, std::unique_ptr<Resource>> _sequenceResources;
	SDL_Renderer* _renderer;
};

}

#endif
