
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
enum class LevelType { Grassland, Desert, IceWorld, Jungle, LavaStone };

//
// ResourceLifeTimes
// - Global: Resource is needed as the game is running (Player Character, GUI Elements, Fonts, Music, ...)
// - Level: Resource is only needed during a specific Level (Ground-Textures, NPC Animations, ...)
// - Sequence: Resource is only for a very short duration like a Cutscene
//
enum class ResourceLifeTime { Global, Level, Sequence };

}

#endif
