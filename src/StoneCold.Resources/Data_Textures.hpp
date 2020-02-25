
#ifndef STONECOLD_DATATEXTURES_H
#define STONECOLD_DATATEXTURES_H

#include "Types.hpp"
#include <unordered_map>
#include <string>

namespace StoneCold::Resources {

//
// All texture names as hardcoded, constant variables
//
const std::string PLAYER_TEXTURE = "textures\\player\\Dwarf_Sprite.png";

//
// All Map Textures hardcoded as unorderd_map
//
const std::unordered_map<StoneCold::LevelType, std::string> MAP_TEXTURES = {
	{ StoneCold::LevelType::Grassland, "textures\\map\\grasslands.png" },
	{ StoneCold::LevelType::Desert, "textures\\map\\desert.png" },
	{ StoneCold::LevelType::Castle, "textures\\map\\castle.png" },
	{ StoneCold::LevelType::Highlands, "textures\\map\\highlands.png" },
	{ StoneCold::LevelType::Arctic, "textures\\map\\arctic.png" }
};

}

#endif
