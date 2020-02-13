
#ifndef STONECOLD_TEXTURERESOURCES_H
#define STONECOLD_TEXTURERESOURCES_H

#include "SDL_Base.hpp"
#include "Resource.hpp"

namespace StoneCold::Resources {

class TextureResource : public Resource {
public:
	TextureResource(const std::string& name, std::unique_ptr<SDL_Texture, SDL_TextureDeleter>&& textureSDL)
		: Resource(name), _textureSDL(std::move(textureSDL)) { }

	//
	// GET, to pass around the raw pointer to the SDL_Texture
	// (But the actual ownership stays with the Texture object)
	//
	SDL_Texture* GetTextureSDL() const { return _textureSDL.get(); }

private:
	std::unique_ptr<SDL_Texture, SDL_TextureDeleter> _textureSDL;
};

}

#endif
