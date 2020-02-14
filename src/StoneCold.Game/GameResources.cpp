
#include "GameResources.hpp"

using namespace StoneCold::Resources;
using namespace StoneCold::Game;

StoneCold::Game::GameResources::GameResources() : _resourceManager(nullptr) { }

bool StoneCold::Game::GameResources::Initialize(ResourceManager* resourceManager) {
	if (resourceManager != nullptr) {
		_resourceManager = resourceManager;
		return false;
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
		//_resourceManager->LoadResource<AnimationResource>(ResourceLifeTime::Global, PLAYER_ANIMATION);
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

		//std::string basePath;
		//switch (type) {
		//case LevelType::Grassland:	basePath = "gassland";	break;
		//case LevelType::Desert:		basePath = "desert";	break;
		//case LevelType::IceWorld:		basePath = "iceworld";	break;
		//case LevelType::Jungle:		basePath = "jungle";	break;
		//case LevelType::LavaStone:	basePath = "lavastone"; break;
		//default: break;
		//}

		//_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, basePath + "/ground.png");
		//_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, basePath + "/wall_1.png");
		//_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, basePath + "/wall_2.png");
		// ...
	}
	catch (const std::exception & ex) {
		std::cout << "Loading Level Resources failed:\n" << ex.what() << std::endl;
	}
}

void StoneCold::Game::GameResources::LoadSequenceResouces() {

}
