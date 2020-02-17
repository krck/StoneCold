
#include "GameResources.hpp"

using namespace StoneCold;
using namespace StoneCold::Resources;
using namespace StoneCold::Game;

bool StoneCold::Game::GameResources::Initialize(ResourceManager* resourceManager) {
	if (resourceManager != nullptr) {
		_resourceManager = resourceManager;
		return true;
	}
	else {
		return false;
	}
}

void GameResources::LoadGlobalResouces() {
	try {
		// First clear the Global Resources
		_resourceManager->UnloadResources(ResourceLifeTime::Global);

		_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Global, PLAYER_TEXTURE);
		_resourceManager->LoadResource<AnimationResource>(ResourceLifeTime::Global, PLAYER_ANIMATION);
		// ...
	}
	catch (const std::exception & ex) {
		std::cout << "Loading Global Resources failed:\n" << ex.what() << std::endl;
	}
}

void GameResources::LoadLevelResouces(LevelType type) {
	try {
		// First clear the Level Resources
		_resourceManager->UnloadResources(ResourceLifeTime::Level);

		if (type == LevelType::Grassland) {
			_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, GRASS_TEXTURE);
			_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, DIRT_TEXTURE);
			_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, WATER_TEXTURE);
		}

		// ...
	}
	catch (const std::exception & ex) {
		std::cout << "Loading Level Resources failed:\n" << ex.what() << std::endl;
	}
}

void StoneCold::Game::GameResources::LoadSequenceResouces() {

}
