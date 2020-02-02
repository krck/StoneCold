
#ifndef STONECOLD_TEXTUREMANAGER_H
#define STONECOLD_TEXTUREMANAGER_H

#include "Types.hpp"
#include "Exception.hpp"
#include "Texture.hpp"
#include <algorithm>
#include <memory>
#include <string>
#include <map>

namespace StoneCold::Resources {

	class TextureManager {
	public:
		TextureManager() : _textures(std::unordered_map<uint, Texture>()) { }
		TextureManager(const TextureManager&) = delete;
		TextureManager& operator=(const TextureManager&) = delete;

		Texture GetTexture();

	private:
		void LoadTexture(SDL_Renderer* renderer, const std::string& fileName);

	private:
		std::unordered_map<uint, Texture> _textures;

	};

}

#endif
