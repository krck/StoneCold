
#ifndef STONECOLD_DATATEXTURES_H
#define STONECOLD_DATATEXTURES_H

#include "Types.hpp"
#include <unordered_map>
#include <string>

namespace StoneCold::Resources {

using namespace StoneCold::Base;

//
// All texture names as hardcoded, constant variables
//
const std::string PLAYER_TEXTURE = "player\\Dwarf_Sprite.png";
const std::string STONECOLD_LOGO = "ui\\StoneCold.png";
const std::string BACKGROUND_IMAGE = "ui\\the_mountain.png";
const std::string GUI_TEXTURE = "ui\\gui_textures.png";

//
// All Map Textures hardcoded as unorderd_map
//
const std::unordered_map<LevelType, std::string> MAP_TEXTURES = {
	{ LevelType::Grassland, "map\\grasslands.png" },
	{ LevelType::Desert, "map\\desert.png" },
	{ LevelType::Castle, "map\\castle.png" },
	{ LevelType::Highlands, "map\\highlands.png" },
	{ LevelType::Arctic, "map\\arctic.png" }
};

//
// All font names as hardcoded, constant variables
//
const std::string FONT_CROM = "fonts\\Crom.ttf";

}

#endif
