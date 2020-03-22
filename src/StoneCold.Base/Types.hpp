
#ifndef STONECOLD_TYPES_H
#define STONECOLD_TYPES_H

#include <cstdint>
#include <typeindex>
#include <typeinfo>

namespace StoneCold::Base {

// StoneCold signed integer typedefs (fastest option, with a width of at least (!) 8, 16, 32 and 64 bits) 
using int8 = std::int_fast8_t;
using int16 = std::int_fast16_t;
using int32 = std::int_fast32_t;
using int64 = std::int_fast64_t;
// StoneCold unsigned integer typedefs (fastest option, with a width of at least (!) 8, 16, 32 and 64 bits) 
using uint8 = std::uint_fast8_t;
using uint16 = std::uint_fast16_t;
using uint32 = std::uint_fast32_t;
using uint64 = std::uint_fast64_t;
// StoneCold custom integer typedefs
using byte = std::uint_fast8_t;
using hash = std::uint_fast64_t;
using mask = std::uint_fast64_t;
using entityId = std::uint_fast32_t;

template<typename T>
inline hash GetTypeHash() noexcept { return std::type_index(typeid(T)).hash_code(); }

//
// All the available Level Types
// (Maybe replace with a runtime-check of which Map-Textures are available)
//
enum class LevelType {
	Grassland,
	Desert,
	Castle,
	Highlands,
	Arctic
};

//
// ResourceLifeTimes
// - Intro, Game and Menu: All have global/infinite lifetime (as long as the game is running) like Player Character, Fonts, GUI Elements
//						   but are split, so they could potentially be unloaded, cleaned up, refreshed, etc. separatley
// - Level:	These Resources are only needed during a specific Level (Ground-Textures, NPC Animations, ...) and will be loaded
//          and unloaded frequently. Only the Resources for one Level will be held in memory at any given time
//
enum class ResourceLifeTime {
	Intro,
	Game,
	Menu,
	Level
};

//
// Event Code send with a custom SDL_UserEvent
// (Not stronly typed, because SDL_Event Codes are int so it must be cast) 
//
enum EventCode {
	Ping,
	ChangeLevel
};

//
// MapTiles used by the Random Map Generator
// These TileTypes will be mapped to a part of the Level-Texture
//
enum class MapTileTypes {
	Placeholder,
	Portal,

	Top_Default,
	Top_Special,

	Floor_Default,
	Floor_Special_1,
	Floor_Special_2,
	Floor_Special_3,
	Floor_Special_4,
	Floor_Shadow,

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

//
// UI Element Attribute
//
enum class UiElementAttribute {
	UIE_Idle,
	UIE_Hover,
	UIE_Selected
};

}

#endif
