
#ifndef STONECOLD_TEXTURE_H
#define STONECOLD_TEXTURE_H

#include "SDL_Base.hpp"
#include <functional>
#include <string>
#include <vector>

namespace StoneCold::Resources {

	enum class TextureType { Player, Map, Background, Enemy };

	class Texture {
	public:
		Texture(const std::string& name, const std::string& path, TextureType type, std::unique_ptr<SDL_Texture, SDL_TextureDeleter>&& textureSDL)
			: Id(std::hash<std::string>()(path)), TextureName(name), TexturePath(path), TextureType(type), _textureSDL(std::move(textureSDL)) { }

		Texture(std::string&& name, std::string&& path, TextureType&& type, std::unique_ptr<SDL_Texture, SDL_TextureDeleter>&& textureSDL)
			: Id(std::hash<std::string>()(path)), TextureName(std::move(name)), TexturePath(std::move(path)), TextureType(std::move(type)), _textureSDL(std::move(textureSDL)) { }

		//
		// GET, to pass around the raw pointer to the SDL_Texture
		// (But the actual ownership stays with the Texture object)
		//
		SDL_Texture* GetTextureSDL() const { return _textureSDL.get(); }

	public:
		const size_t Id;
		const std::string TextureName;
		const std::string TexturePath;
		const TextureType TextureType;
	private:
		std::unique_ptr<SDL_Texture, SDL_TextureDeleter> _textureSDL;
	};

}

#endif
