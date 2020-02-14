
#ifndef STONECOLD_GAMERESOURCES_H
#define STONECOLD_GAMERESOURCES_H

#include "ResourceManager.hpp"
#include <iostream>

namespace StoneCold::Game {

	using namespace StoneCold::Resources;

	//
	// All the bread-and-butter Video Game level types
	//
	enum class LevelType { Grassland, Desert, IceWorld, Jungle, LavaStone };


	//
	// Definitions of what Resources should be loaded
	// This includes Player Textures, GUI Fonts, NPC Animations, ...
	//
	class GameResources {
	private:
		ResourceManager* _resourceManager;

	public:
		GameResources(ResourceManager* resourceManager) : _resourceManager(resourceManager) {}

		void LoadGlobalResouces() {
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

		void LoadLevelResouces(LevelType type) {
			try {
				// First clear the Level Resources
				_resourceManager->UnloadResources(ResourceLifeTime::Level);

				std::string basePath;
				switch (type) {
				case LevelType::Grassland:	basePath = "gassland";	break;
				case LevelType::Desert:		basePath = "desert";	break;
				case LevelType::IceWorld:	basePath = "iceworld";	break;
				case LevelType::Jungle:		basePath = "jungle";	break;
				case LevelType::LavaStone:	basePath = "lavastone"; break;
				default: break;
				}

				_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, basePath + "/ground.png");
				_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, basePath + "/wall_1.png");
				_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, basePath + "/wall_2.png");
				// ...
			}
			catch (const std::exception & ex) {
				std::cout << "Loading Level Resources failed:\n" << ex.what() << std::endl;
			}
		}

	};

}

#endif
