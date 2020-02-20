
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

		// Get a new, randomly generated Map Texture
		auto levelType = (LevelType)(rand() % 4 + 0);
		std::string texturePath = MAP_TEXTURES.find(levelType)->second;
		_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, texturePath);

		// Get a new, randomly generated Map Layout
		auto mapData = _engine->GetNewMap();
		auto texture = _resourceManager->GetResource<TextureResource>(texturePath);
		auto renderPtr = _engine->GetSDLRenderer();

		for (int row = 0; row < mapData.size(); row++) {
			for (int column = 0; column < mapData[row].size(); column++) {
				// Map tile position based on row/column within the mapLayout
				const auto type = mapFrames.find(mapData[row][column])->second;
				auto tile = MapTile(renderPtr, texture, Vec2(column * 96.f, row * 96.f), Vec2(32.f, 32.f), type.first, type.second, 0);
				_engine->AddNewGameObject(std::make_unique<MapTile>(tile));
			}
		}

		// ...
	}
	catch (const std::exception & ex) {
		std::cout << "Loading Level Resources failed:\n" << ex.what() << std::endl;
	}
}

void StoneCold::Game::SimulationManager::LoadSequenceResouces() {

}
