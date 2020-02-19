
#ifndef STONECOLD_DATAANIMATIONS_H
#define STONECOLD_DATAANIMATIONS_H

#include "AnimationResource.hpp"

namespace StoneCold::Resources {

//
// All animation names as hardcoded, constant variables
//
const std::string PLAYER_ANIMATION = "Dwarf_Sprite_Animation";
const std::string MAP_ANIMATION = "Map_Animation";


//
// Animation data as hardcoded, constat variables
//
const auto playerAnimation = std::unordered_map<std::string, Animation>({
	{"idle", Animation({ {0,0,32,32}, {32,0,32,32}, {64,0,32,32}, {96,0,32,32}, {128,0,32,32} }, 180) },
	{"walk", Animation({ {0,32,32,32}, {32,32,32,32}, {64,32,32,32}, {96,32,32,32}, {128,32,32,32}, {160,32,32,32}, {192,32,32,32}, {224,32,32,32} }, 80) },
	{"atk2", Animation({ {0,64,32,32}, {32,64,32,32}, {64,64,32,32}, {96,64,32,32}, {128,64,32,32}, {160,64,32,32}, {192,64,32,32} }, 100) },
	{"atk1", Animation({ {0,96,32,32}, {32,96,32,32}, {64,96,32,32}, {96,96,32,32}, {128,96,32,32}, {160,96,32,32} }, 100) },
	{"atk3", Animation({ {0,128,32,32}, {32,128,32,32} }, 100) },
	{"jump", Animation({ {0,160,32,32}, {32,160,32,32}, {64,160,32,32}, {96,160,32,32}, {128,160,32,32} }, 100) },
	{"hurt", Animation({ {0,192,32,32}, {32,192,32,32}, {64,192,32,32}, {96,192,32,32} }, 100) },
	{"dead", Animation({ {0,224,32,32}, {32,224,32,32}, {64,224,32,32}, {96,224,32,32}, {128,224,32,32}, {160,224,32,32}, {192,224,32,32} }, 100) }
	});

const auto mapAnimation = std::unordered_map<std::string, Animation>({
	{"wall_top",			Animation({ {0,0,32,32} }, 0) },
	{"corner_top",			Animation({	{32,0,32,32} }, 0) },
	{"middle_horizontal",	Animation({ {64,0,32,32} }, 0) },
	{"endblock_top",		Animation({ {96,0,32,32} }, 0) },
	{"wall_default",		Animation({ {0,32,32,32} }, 0) },
	{"wall_side",			Animation({ {32,32,32,32} }, 0) },
	{"middle_vertical",		Animation({ {64,32,32,32} }, 0) },
	{"endblock_bottom",		Animation({ {96,32,32,32} }, 0) },
	{"wall_bottom",			Animation({ {0,64,32,32} }, 0) },
	{"corner_bottom",		Animation({ {32,64,32,32} }, 0) },
	{"wall_default_2",		Animation({ {64,64,32,32} }, 0) },
	{"endblock_side",		Animation({ {96,64,32,32} }, 0) },
	{"floor_bottom",		Animation({ {0,96,32,32} }, 0) },
	{"floor_corner",		Animation({ {32,96,32,32} }, 0) },
	{"floor_default",		Animation({ {64,96,32,32} }, 0) },
	{"floor_default_2",		Animation({ {96,96,32,32} }, 0) }
});

//
// Map all animation names with their actual animation data
//
const auto AnimationData = std::unordered_map<std::string, std::unordered_map<std::string, Animation>>({
	{ PLAYER_ANIMATION, playerAnimation },
	{ MAP_ANIMATION, mapAnimation }
});

}

#endif
