
#include "LevelManager.hpp"

using namespace StoneCold;
using namespace StoneCold::Resources;
using namespace StoneCold::Game;

bool LevelManager::Initialize(ResourceManager* resourceManager, GameResources* gameResources) {
	if (resourceManager != nullptr && gameResources != nullptr) {
		_resourceManager = resourceManager;
		_gameResources = gameResources;
		return true;
	}
	else {
		return false;
	}
}

void LevelManager::LoadLevel(EngineCore* engine, LevelType type, const std::vector<std::vector<int>> mapLayout) {
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
			auto tile = MapTile(renderPtr, texMap[texId], Vec2(column * 64.f, row * 64.f), Vec2(64.f, 64.f), texId);
			engine->AddNewGameObject(std::make_unique<MapTile>(tile));
		}
	}
}
