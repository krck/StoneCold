
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
enum class LevelType { Grassland, Desert, Stone, Ice };

//
// ResourceLifeTimes
// - Global: Resource is needed as the game is running (Player Character, GUI Elements, Fonts, Music, ...)
// - Level: Resource is only needed during a specific Level (Ground-Textures, NPC Animations, ...)
// - Sequence: Resource is only for a very short duration like a Cutscene
//
enum class ResourceLifeTime { Global, Level, Sequence };

//
// MapTiles used by the Random Map Generator
// These TileTypes will be mapped to a Texture
//
enum class MapTileTypes {
	Empty,
	Floor_Default,
	Floor_Special_1,
	Floor_Special_2,
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
