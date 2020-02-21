
#include "SimulationManager.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;
using namespace StoneCold::Resources;
using namespace StoneCold::Game;

bool StoneCold::Game::SimulationManager::Initialize(EngineCore* engine, ResourceManager* resourceManager) {
	if (engine != nullptr && resourceManager != nullptr) {
		_engine = engine;
		_resourceManager = resourceManager;
		return true;
	}
	else {
		return false;
	}
}

void SimulationManager::LoadGlobalResouces() {
	try {
		// First clear the Global Resources
		_resourceManager->UnloadResources(ResourceLifeTime::Global);
		_engine->UnloadGameObjects(ResourceLifeTime::Global);

		_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Global, PLAYER_TEXTURE);
		_resourceManager->LoadResource<AnimationResource>(ResourceLifeTime::Global, PLAYER_ANIMATION);
		// ...

		auto renderPtr = _engine->GetSDLRenderer();
		auto playerTexture = _resourceManager->GetResource<TextureResource>(PLAYER_TEXTURE);
		auto playerAnimation = _resourceManager->GetResource<AnimationResource>(PLAYER_ANIMATION);
		auto pc = PlayerCharacter(renderPtr, playerTexture, playerAnimation, Vec2(), Vec2(32, 32), 3, 200);
		_engine->AddPlayer(std::make_unique<PlayerCharacter>(pc));
	}
	catch (const std::exception & ex) {
		std::cout << "Loading Global Resources failed:\n" << ex.what() << std::endl;
	}
}

void SimulationManager::LoadLevelResouces() {
	try {
		// First clear the Level Resources
		_resourceManager->UnloadResources(ResourceLifeTime::Level);
		_engine->UnloadGameObjects(ResourceLifeTime::Level);

		// Get a new, randomly generated Map Texture
		auto levelType = (LevelType)(rand() % 4 + 0);
		std::string texturePath = MAP_TEXTURES.find(levelType)->second;
		_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, texturePath);

		// Get a new, randomly generated Map Layout
		auto mapData = _mapGenerator.GenerateMap(Vec2i(60, 60));
		auto spawnPos = _mapGenerator.GetStartEndPositions();
		auto texture = _resourceManager->GetResource<TextureResource>(texturePath);
		auto renderPtr = _engine->GetSDLRenderer();

		// Create the actual MapTiles, based on the Layout and the loaded MapTexture
		for (int row = 0; row < mapData.size(); row++) {
			for (int column = 0; column < mapData[row].size(); column++) {
				// Map tile position based on row/column within the mapLayout
				const auto type = mapFrames.find(mapData[row][column]);
				const auto frame = type->second;
				auto tile = MapTile(renderPtr, texture, Vec2(column * 96.f, row * 96.f), Vec2(32.f, 32.f), frame.first, frame.second, type->first);
				_engine->AddNewMapObject(texture->Id, std::make_shared<MapTile>(tile));
			}
		}

		// Update the Players position to fit a random spawn point
		_engine->SetPlayerPosition(Vec2(spawnPos.first.X * 96.f, spawnPos.first.Y * 96.f));

		// ...
	}
	catch (const std::exception & ex) {
		std::cout << "Loading Level Resources failed:\n" << ex.what() << std::endl;
	}
}

void StoneCold::Game::SimulationManager::LoadSequenceResouces() {
	try {
		// First clear the Sequence Resources
		_resourceManager->UnloadResources(ResourceLifeTime::Sequence);
		_engine->UnloadGameObjects(ResourceLifeTime::Sequence);

		// ...
	}
	catch (const std::exception & ex) {
		std::cout << "Loading Sequence Resources failed:\n" << ex.what() << std::endl;
	}
}
