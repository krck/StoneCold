
#ifndef STONECOLD_RESOURCECORE_H
#define STONECOLD_RESOURCECORE_H

#include <iostream>

namespace StoneCold::Resources {

	//
	// All the bread-and-butter Video Game level types
	//
	enum class LevelType { Grassland, Desert, IceWorld, Jungle, LavaStone };

	//
	// Definitions of what Resources should be loaded
	//
	class GameResources {
	private:
		ResourceManager* _resourceManager;
		
	public:
		GameResources(ResourceManager* resourceManager)
			: _resourceManager(resourceManager) {}
		
		void LoadGlobalResouces() {
			// always clear the global resources
			RessourceManager.UnloadResources(Global);
			
			try {
				_resourceManager->LoadResource<TextureResource>(Global, "player.png");
				_resourceManager->LoadResource<AnimationResource>(Global, "player.png");	
				...
			}
			catch () {}
		}

		void LoadLevelResouces(LevelType type) {
			// Always clear the last Levels Resources
			RessourceManager.UnloadResources(Level);
			
			try {
				std::string basePath;
				switch(type) {
					case GrassLand: basePath = "gassland"; break;
					case Desert: basePath = "desert"; break;
					case IceWorld: basePath = "iceworld"; break;
					case Jungle: basePath = "jungle"; reak;
					case LavaStone: basePath = "lavastone"; break;
					default: 
				}
				
				_resourceManager->LoadResource<TextureResource>(Level, basePath + "/ground.png");
				_resourceManager->LoadResource<TextureResource>(Level, basePath + "/wall_1.png");
				_resourceManager->LoadResource<TextureResource>(Level, basePath + "/wall_2.png");
				...
			}
			catch () {}
		}
	
	};
	
	
	
	class GameCore {
	
	private:
		RessourceManager _ressourceManager;
		GameResources _gameResources;
		
	public:
		void Init() {
			// ... init enginge, ....
			// ... init resourcemanager ....
			_gameResources = GameResources(&_resourceManager);
			
			_gameResources.LoadGlobalResouces();
			_gameResources.LoadLevelResouces(Level1);
			
			// ...
			
			gameObjects.add<Player>(RessourceManager.GetResource<TextureResource>("player")
					       ,RessourceManager.GetResource<AnimationResource>("player")
					       , ...)
			
			// ...
		}
		
	};
	
	
	
	
}

#endif
