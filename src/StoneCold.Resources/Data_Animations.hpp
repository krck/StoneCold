
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
	{"idle", Animation({ {0,0,32,32}, {32,0,32,32}, {64,0,32,32}, {96,0,32,32}, {128,0,32,32} }, 180) },
	{"walk", Animation({ {0,32,32,32}, {32,32,32,32}, {64,32,32,32}, {96,32,32,32}, {128,32,32,32}, {160,32,32,32}, {192,32,32,32}, {224,32,32,32} }, 80) },
	{"atk2", Animation({ {0,64,32,32}, {32,64,32,32}, {64,64,32,32}, {96,64,32,32}, {128,64,32,32}, {160,64,32,32}, {192,64,32,32} }, 100) },
	{"atk1", Animation({ {0,96,32,32}, {32,96,32,32}, {64,96,32,32}, {96,96,32,32}, {128,96,32,32}, {160,96,32,32} }, 100) },
	{"atk3", Animation({ {0,128,32,32}, {32,128,32,32} }, 100) },
	{"jump", Animation({ {0,160,32,32}, {32,160,32,32}, {64,160,32,32}, {96,160,32,32}, {128,160,32,32} }, 100) },
	{"hurt", Animation({ {0,192,32,32}, {32,192,32,32}, {64,192,32,32}, {96,192,32,32} }, 100) },
	{"dead", Animation({ {0,224,32,32}, {32,224,32,32}, {64,224,32,32}, {96,224,32,32}, {128,224,32,32}, {160,224,32,32}, {192,224,32,32} }, 100) }
});

const auto mapFrames = std::unordered_map<MapTileTypes, std::pair<SDL_Rect, SDL_RendererFlip>>({
	{MapTileTypes::Wall_Top,				{ {0,0,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Corner_Top_Left,			{ {32,0,32,32}, SDL_RendererFlip::SDL_FLIP_HORIZONTAL } },
	{MapTileTypes::Corner_Top_Right,		{ {32,0,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Middle_Block_Vertical,	{ {64,0,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Endblock_Top,			{ {96,0,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Empty,					{ {0,32,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Wall_Left,				{ {32,32,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Wall_Right,				{ {32,32,32,32}, SDL_RendererFlip::SDL_FLIP_HORIZONTAL } },
	{MapTileTypes::Middle_Block_Horizontal,	{ {64,32,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Endblock_Bottom,			{ {96,32,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Wall_Bottom,				{ {0,64,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Corner_Bottom_Left,		{ {32,64,32,32}, SDL_RendererFlip::SDL_FLIP_HORIZONTAL } },
	{MapTileTypes::Corner_Bottom_Right,		{ {32,64,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Floor_Special_2,			{ {64,64,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Endblock_Left,			{ {96,64,32,32}, SDL_RendererFlip::SDL_FLIP_HORIZONTAL } },
	{MapTileTypes::Endblock_Right,			{ {96,64,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Floor_Bottom,			{ {0,96,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Floor_Corner_Left,		{ {32,96,32,32}, SDL_RendererFlip::SDL_FLIP_HORIZONTAL } },
	{MapTileTypes::Floor_Corner_Right,		{ {32,96,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Floor_Default,			{ {64,96,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Floor_Special_1,			{ {96,96,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } },
	{MapTileTypes::Portal,					{ {0,32,32,32}, SDL_RendererFlip::SDL_FLIP_NONE } }
});

//
// Map all animation names with their actual animation data
//
const auto AnimationData = std::unordered_map<std::string, std::unordered_map<std::string, Animation>>({
	{ PLAYER_ANIMATION, playerAnimation }
});

}

#endif
