
#ifndef STONECOLD_TEXTUREMANAGER_H
#define STONECOLD_TEXTUREMANAGER_H

#include "Types.hpp"
#include "IManager.hpp"
#include "Exception.hpp"
#include "Texture.hpp"
#include <algorithm>
#include <memory>
#include <string>
#include <map>

namespace StoneCold::Resources {

class TextureManager : public IManager {
public:
	TextureManager(SDL_Renderer* renderer) : _textures(std::unordered_map<hash64, Texture>()), _renderer(renderer) { }
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	virtual bool LoadResources(const std::vector<Resource>& resources) override;
	virtual bool UnloadResources(const std::vector<uint>& resourceIds) override;

private:
	void LoadTexture(const Resource& resource);

private:
	std::unordered_map<hash64, Texture> _textures;
	SDL_Renderer* _renderer;

};

}

#endif
