
#include "MapManager.hpp"

using namespace StoneCold::Resources;
using namespace StoneCold::Game;

bool MapManager::Initialize(ResourceManager* resourceManager, GameResources* gameResources) {
	if (resourceManager != nullptr && gameResources != nullptr) {
		_resourceManager = resourceManager;
		_gameResources = gameResources;
		return true;
	}
	else {
		return false;
	}
}

void MapManager::LoadMap(EngineCore* engine, LevelType type, const std::vector<std::vector<int>> mapLayout) {
	// Load the specific Level Resources
	_gameResources->LoadLevelResouces(LevelType::Grassland);

	// Get the textures and create the MapTiles
	auto texMap = std::unordered_map<int, TextureResource*>({
		{ 0, _resourceManager->GetResource<TextureResource>(WATER_TEXTURE) },
		{ 1, _resourceManager->GetResource<TextureResource>(GRASS_TEXTURE) },
		{ 2, _resourceManager->GetResource<TextureResource>(DIRT_TEXTURE) }
	});

	auto renderPtr = engine->GetSDLRenderer();
	for (int row = 0; row < mapLayout.size(); row++) {
		for (int column = 0; column < mapLayout[row].size(); column++) {
			// Map tile position based on row/column within the mapLayout
			const auto& texId = mapLayout[row][column];
			auto grassTile = MapTile(renderPtr, texMap[texId], Vec2i(column * 64, row * 64), Vec2i(64, 64));
			engine->AddNewGameObject(std::make_unique<MapTile>(grassTile));
		}
	}
}
