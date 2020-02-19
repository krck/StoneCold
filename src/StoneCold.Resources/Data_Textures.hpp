
#ifndef STONECOLD_DATATEXTURES_H
#define STONECOLD_DATATEXTURES_H

#include "Types.hpp"
#include <unordered_map>
#include <string>

namespace StoneCold::Resources {

//
// All texture names as hardcoded, constant variables
//
const std::string PLAYER_TEXTURE = "textures\\Dwarf_Sprite.png";

//
// All Map Textures hardcoded as unorderd_map
//
const std::unordered_map<StoneCold::LevelType, std::string> MAP_TEXTURES = {
	{ StoneCold::LevelType::Grassland, "textures\\map_grassland.png" },
	{ StoneCold::LevelType::Desert, "textures\\map_desert.png" },
	{ StoneCold::LevelType::Stone, "textures\\map_stone.png" },
	{ StoneCold::LevelType::Ice, "textures\\map_ice.png" }
};

}

#endif
