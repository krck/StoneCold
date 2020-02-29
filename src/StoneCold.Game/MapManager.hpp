
#ifndef STONECOLD_MAPMANAGER_H
#define STONECOLD_MAPMANAGER_H

#include "Vec2.hpp"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <chrono>

namespace StoneCold::Game {

//
// 2d procedural Map Generator
//
// Using the Drunkard-Walk procedural generation algorithm (one of the most simple dungeon map generators)
// This Code is based on a Tutorial by William Beaty (https://www.youtube.com/watch?v=I74I_MhZIK8)
// (... which in turn was based on the game Nuclear Throne)
//
class MapManager {
private:
	struct Walker { Vec2i dir = Vec2i(), pos = Vec2i(); };

public:
	MapManager() { }
	MapManager(const MapManager&) = delete;
	MapManager& operator=(const MapManager&) = delete;

	const std::vector<std::vector<MapTileTypes>>& GenerateMap(Vec2i size);
	inline std::pair<Vec2i, Vec2i> GetStartEndPositions() { return _mapStartEndPositions;  }

	~MapManager() = default;

private:
	//
	// Use random (drunk) _walkers to create a base surface area for the Map
	//
	void CreateFloor();

	//
	// Create "placeholder" walls around the base surface area of the Map
	// and remove all lone wall tiles to create smoother, open spaces
	//
	void CreateWalls();

	//
	// Finally replace all placeholder Empty, Floors and Walls with the acutal
	// MapTiles that will later be rendered (Top walls, bottom walls, corners, ...)
	//
	void SetMapTiles();

	//
	// Get a random direction Vector (Up, down, left or right)
	//
	Vec2i RandomDirection();

	//
	// Removes one element form a vector at the specified index
	//
	template <typename T>
	void remove_at(std::vector<T>& v, typename std::vector<T>::size_type i) {
		std::swap(v[i], v.back());
		v.pop_back();
	}

private:
	std::pair<Vec2i, Vec2i> _mapStartEndPositions;
	std::vector<std::vector<MapTileTypes>> _grid;
	std::vector<Walker> _walkers;
	Vec2i _mapSize;

	// Could be variable, but these settings yield good results
	const float _chanceWalkerChangeDir = 0.5;
	const float _chanceWalkerUpdate = 0.01f;
	const float _percentToFill = 0.25f;
	const int _maxWalkers = 10;
};

}

#endif