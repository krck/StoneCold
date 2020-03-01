
#ifndef STONECOLD_TYPES_H
#define STONECOLD_TYPES_H

namespace StoneCold {

// Additional base types
typedef unsigned char		byte;
typedef unsigned int		uint;
typedef unsigned __int8		uint8;
typedef unsigned __int64	hash64;

//
// All the bread-and-butter Video Game level types
//
enum class LevelType { Grassland, Desert, Castle, Highlands, Arctic };

//
// ResourceLifeTimes
// - Intro, Game and Menu: All have global/infinite lifetime (as long as the game is running) like Player Character, Fonts, GUI Elements
//						   but are split, so they could potentially be unloaded, cleaned up, refreshed, etc. separatley
// - Level:	These Resources are only needed during a specific Level (Ground-Textures, NPC Animations, ...) and will be loaded
//          and unloaded frequently. Only the Resources for one Level will be held in memory at any given time
//
enum class ResourceLifeTime { Intro, Game, Menu, Level };

//
// MapTiles used by the Random Map Generator
// These TileTypes will be mapped to a Texture
//
enum class MapTileTypes {
	Empty,
	Floor_Default,
	Floor_Special_1,
	Floor_Special_2,
	Floor_Special_3,
	Floor_Bottom,
	Floor_Corner_Left,
	Floor_Corner_Right,
	Placeholder,
	Portal,

	Wall_Top,
	Wall_Left,
	Wall_Right,
	Wall_Bottom,

	Corner_Top_Left,
	Corner_Top_Right,
	Corner_Bottom_Left,
	Corner_Bottom_Right,

	Endblock_Top,
	Endblock_Left,
	Endblock_Right,
	Endblock_Bottom,

	Middle_Block_Horizontal,
	Middle_Block_Vertical,
};

}

#endif
