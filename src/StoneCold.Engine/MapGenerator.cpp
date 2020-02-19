
#include "MapGenerator.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

const std::vector<std::vector<MapTileTypes>>&  MapGenerator::GenerateMap(Vec2i size) {
	// Set _grid size and create a _grid with empty spaces and reset the _walkers
	_mapSize = size;
	_spawnPos = Vec2i((_mapSize.X / 2), (_mapSize.Y / 2));
	_grid = std::vector<std::vector<MapTileTypes>>(_mapSize.X, std::vector<MapTileTypes>(_mapSize.Y, MapTileTypes::Empty));
	_walkers = std::vector<Walker>();

	CreateFloor();
	CreateWalls();
	SetMapTiles();

	return _grid;
}

void MapGenerator::CreateFloor() {
	// Create and add the first walker
	auto newWalker = Walker();
	newWalker.dir = RandomDirection();
	newWalker.pos = _spawnPos;
	_walkers.push_back(newWalker);

	float random = 0.f;
	float floorCount = 0.f;
	for (int iterations = 0; iterations < 100000; iterations++) {
		// Random chance: Destroy a Walker (Only if its not the only one, and at a low chance)
		random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		if (random < _chanceWalkerUpdate && _walkers.size() > 1) {
			remove_at(_walkers, (rand() % ((_walkers.size() - 1) + 0)));
		}

		// Move all _walkers
		for (auto& walker : _walkers) {
			// Random chance: Walker picks a new direction
			random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
			if (random < _chanceWalkerChangeDir)
				walker.dir = RandomDirection();

			// Update the position, based on the direction
			walker.pos.X += walker.dir.X;
			walker.pos.Y += walker.dir.Y;
			// Avoid the boarder of the _grid
			// Clamp x,y to leave at least 1 space to the boarder (Room for walls)
			walker.pos.X = std::clamp(walker.pos.X, 7, _mapSize.X - 8);
			walker.pos.Y = std::clamp(walker.pos.Y, 7, _mapSize.Y - 8);

			// Create a Floor at the position of every walker, if there is non already
			if (_grid[walker.pos.X][walker.pos.Y] != MapTileTypes::Floor_Default) {
				_grid[walker.pos.X][walker.pos.Y] = MapTileTypes::Floor_Default;
				floorCount++;
			}
		}

		// Random chance: Spawn a new Walker (Only if # of _walkers < max, and at a low chance)
		random = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
		if (random < _chanceWalkerUpdate && _walkers.size() < _maxWalkers) {
			auto newWalker = Walker();
			newWalker.dir = RandomDirection();
			newWalker.pos = _walkers.front().pos;
			_walkers.push_back(newWalker);
		}

		// Calculate the Percentage of tiles that are "Floor" and exit if enough is filled
		if ((floorCount / (float)(_mapSize.X * _mapSize.Y)) > _percentToFill)
			return;
	}
}

void MapGenerator::CreateWalls() {
	// Loop though every _grid space and check if theres a floor, with
	// empty space around it. This will be changed to a Wall-Placeholder
	for (int i = 0; i < _grid.size(); i++) {
		for (int j = 0; j < _grid[i].size(); j++) {
			if (_grid[i][j] == MapTileTypes::Floor_Default) {
				if (_grid[i - 1][j] == MapTileTypes::Empty) {
					_grid[i - 1][j] = MapTileTypes::Placeholder;
				}
				if (_grid[i + 1][j] == MapTileTypes::Empty) {
					_grid[i + 1][j] = MapTileTypes::Placeholder;
				}
				if (_grid[i][j - 1] == MapTileTypes::Empty) {
					_grid[i][j - 1] = MapTileTypes::Placeholder;
				}
				if (_grid[i][j + 1] == MapTileTypes::Empty) {
					_grid[i][j + 1] = MapTileTypes::Placeholder;
				}
			}
		}
	}

	// Loop though every _grid space and check if there is now a single
	// Wall surrounded by Floor tiles. If so, replace it with Floor.
	for (int i = 0; i < _grid.size(); i++) {
		for (int j = 0; j < _grid[i].size(); j++) {
			if (_grid[i][j] == MapTileTypes::Placeholder) {
				bool allFloors = true;
				// Check each side to see if they are all floors
				for (int checkX = -1; checkX <= 1; checkX++) {
					for (int checkY = -1; checkY <= 1; checkY++) {
						if (i + checkX < 0 || i + checkX > _mapSize.X - 1 ||
							j + checkY < 0 || j + checkY > _mapSize.Y - 1) {
							// Skip checks that are out of range
							continue;
						}
						if ((checkX != 0 && checkY != 0) || (checkX == 0 && checkY == 0)) {
							// Skip corners and center
							continue;
						}
						if (_grid[i + checkX][j + checkY] != MapTileTypes::Floor_Default) {
							allFloors = false;
						}
					}
				}
				if (allFloors) {
					_grid[i][j] = MapTileTypes::Floor_Default;
				}
			}
		}
	}
}

void MapGenerator::SetMapTiles() {
	for (int i = 0; i < _grid.size(); i++) {
		for (int j = 0; j < _grid[i].size(); j++) {
			if (_grid[i][j] == MapTileTypes::Placeholder) {
				std::vector<bool> tmp{
					_grid[i - 1][j] == MapTileTypes::Floor_Default,	// top
					_grid[i + 1][j] == MapTileTypes::Floor_Default,	// bottom
					_grid[i][j - 1] == MapTileTypes::Floor_Default,	// right
					_grid[i][j + 1] == MapTileTypes::Floor_Default	// left
				};
				int floorCount = (tmp[0] + tmp[1] + tmp[2] + tmp[3]);

				// If floor is in 3 locations around
				if (floorCount == 3) {
					if (!tmp[0]) {
						_grid[i][j] = MapTileTypes::Endblock_Bottom;
						//_grid[i + 1][j] = MapTileTypes::Floor_Bottom;
					}
					else if (!tmp[1])
						_grid[i][j] = MapTileTypes::Endblock_Top;
					else if (!tmp[2]) {
						_grid[i][j] = MapTileTypes::Endblock_Right;
						//_grid[i + 1][j] = MapTileTypes::Floor_Corner_Right;
					}
					else {
						_grid[i][j] = MapTileTypes::Endblock_Left;
						//_grid[i + 1][j] = MapTileTypes::Floor_Corner_Left;
					}
				}
				// If floor is in 2 locations around
				if (floorCount == 2) {
					if (tmp[0] && tmp[2])
						_grid[i][j] = MapTileTypes::Corner_Top_Left;
					else if (tmp[0] && tmp[3])
						_grid[i][j] = MapTileTypes::Corner_Top_Right;
					else if (tmp[1] && tmp[2]) {
						_grid[i][j] = MapTileTypes::Corner_Bottom_Left;
						//_grid[i + 1][j] = MapTileTypes::Floor_Corner_Left;
					}
					else if (tmp[1] && tmp[3]) {
						_grid[i][j] = MapTileTypes::Corner_Bottom_Right;
						//_grid[i + 1][j] = MapTileTypes::Floor_Corner_Right;
					}
					else if (tmp[0] && tmp[1]) {
						_grid[i][j] = MapTileTypes::Middle_Block_Horizontal;
						/*_grid[i + 1][j] = MapTileTypes::Floor_Bottom;*/
					}
					else
						_grid[i][j] = MapTileTypes::Middle_Block_Vertical;
				}
				// If floor is in 1 location around
				if (floorCount == 1) {
					if (tmp[0])
						_grid[i][j] = MapTileTypes::Wall_Top;
					else if (tmp[1]) {
						_grid[i][j] = MapTileTypes::Wall_Bottom;
						//_grid[i + 1][j] = MapTileTypes::Floor_Bottom;
					}
					else if (tmp[2])
						_grid[i][j] = MapTileTypes::Wall_Right;
					else
						_grid[i][j] = MapTileTypes::Wall_Left;
				}
			}
		}
	}
}

Vec2i MapGenerator::RandomDirection() {
	// Random direction (Number between 1 and 4)
	int choice = (rand() % 4 + 1);
	switch (choice) {
	case 1: return Vec2i(0, -1); break;	// down
	case 2: return Vec2i(-1, 0); break;	// left
	case 3: return Vec2i(0, 1); break;	// up
	default: return Vec2i(1, 0); break;	// right
	}
}
