
#ifndef STONECOLD_DATATEXTURES_H
#define STONECOLD_DATATEXTURES_H

#include "Types.hpp"
#include <unordered_map>
#include <string>

namespace StoneCold::Resources {

//
// All texture names as hardcoded, constant variables
//
const std::string PLAYER_TEXTURE = "player\\Dwarf_Sprite.png";
const std::string BACKGROUND_IMAGE = "background\\the_mountain.png";

//
// All Map Textures hardcoded as unorderd_map
//
const std::unordered_map<StoneCold::LevelType, std::string> MAP_TEXTURES = {
	{ StoneCold::LevelType::Grassland, "map\\grasslands.png" },
	{ StoneCold::LevelType::Desert, "map\\desert.png" },
	{ StoneCold::LevelType::Castle, "map\\castle.png" },
	{ StoneCold::LevelType::Highlands, "map\\highlands.png" },
	{ StoneCold::LevelType::Arctic, "map\\arctic.png" }
};

//
// All font names as hardcoded, constant variables
//
const std::string FONT_CROM = "fonts\\Crom.ttf";

}

#endif
