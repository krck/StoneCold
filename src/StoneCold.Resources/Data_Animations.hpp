
#ifndef STONECOLD_DATAANIMATIONS_H
#define STONECOLD_DATAANIMATIONS_H

#include "AnimationResource.hpp"

namespace StoneCold::Resources {

//
// All animation names as hardcoded, constant variables
//
const std::string PLAYER_ANIMATION = "Dwarf_Sprite_Animation";

//
// Animation data as hardcoded, constat variables
//
const auto playerAnimation = std::unordered_map<std::string, Animation>({
	{"idle", Animation({ {0,0,34,34}, {34,0,34,34}, {68,0,34,34}, {102,0,34,34}, {136,0,34,34} }, 180) },
	{"walk", Animation({ {0,34,34,34}, {34,34,34,34}, {68,34,34,34}, {102,34,34,34}, {136,34,34,34}, {170,34,34,34}, {204,34,34,34}, {238,34,34,34} }, 80) },
	{"atk2", Animation({ {0,68,34,34}, {34,68,34,34}, {68,68,34,34}, {102,68,34,34}, {136,68,34,34}, {170,68,34,34}, {204,68,34,34} }, 100) },
	{"atk1", Animation({ {0,102,34,34}, {34,102,34,34}, {68,102,34,34}, {102,102,34,34}, {136,102,34,34}, {170,102,34,34} }, 100) },
	{"atk3", Animation({ {0,136,34,34}, {34,136,34,34} }, 100) },
	{"jump", Animation({ {0,170,34,34}, {34,170,34,34}, {68,170,34,34}, {102,170,34,34}, {136,170,34,34} }, 100) },
	{"hurt", Animation({ {0,204,34,34}, {34,204,34,34}, {68,204,34,34}, {102,204,34,34} }, 100) },
	{"dead", Animation({ {0,238,34,34}, {34,238,34,34}, {68,238,34,34}, {102,238,34,34}, {136,238,34,34}, {170,238,34,34}, {204,238,34,34} }, 100) }
});

//
// Map all animation names with their actual animation data
//
const auto AnimationData = std::unordered_map<std::string, std::unordered_map<std::string, Animation>>({
	{ PLAYER_ANIMATION, playerAnimation }
});

}

#endif
