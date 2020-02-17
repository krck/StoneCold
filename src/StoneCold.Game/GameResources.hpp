
#ifndef STONECOLD_GAMERESOURCES_H
#define STONECOLD_GAMERESOURCES_H

#include "ResourceManager.hpp"
#include <iostream>

namespace StoneCold::Game {

using namespace StoneCold::Resources;

//
// Definitions of what Resources should be loaded
// This includes Player Textures, GUI Fonts, NPC Animations, ...
//
class GameResources {
public:
	GameResources() : _resourceManager(nullptr) { }
	GameResources(const GameResources&) = delete;
	GameResources& operator=(const GameResources&) = delete;

	bool Initialize(ResourceManager* resourceManager);

	void LoadGlobalResouces();
	void LoadLevelResouces(LevelType type);
	void LoadSequenceResouces();

	~GameResources() = default;

private:
	ResourceManager* _resourceManager;
};

}

#endif
