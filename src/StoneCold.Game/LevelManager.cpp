
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

void LevelManager::LoadLevel(EngineCore* engine, LevelType type) {
	// Get a new, randomly generated Map
	auto mapData = engine->GetNewMap();

	_gameResources->LoadLevelResouces(LevelType::Grassland);
	auto animation = _resourceManager->GetResource<AnimationResource>(MAP_ANIMATION);
	auto texture = _resourceManager->GetResource<TextureResource>(GRASSLAND_TEXTURE);
	auto renderPtr = engine->GetSDLRenderer();
	const auto& an = animation->Animations;

	for (int row = 0; row < mapData.size(); row++) {
		for (int column = 0; column < mapData[row].size(); column++) {
			const auto type = mapData[row][column];
			auto srcRect = SDL_Rect();
			auto flip = SDL_RendererFlip::SDL_FLIP_NONE;
			switch (type) {
			case MapTileTypes::Empty: srcRect = an.find("wall_default")->second.FramePositions.front(); break;
			case MapTileTypes::Floor: srcRect = an.find("floor_default")->second.FramePositions.front(); break;
			case MapTileTypes::Placeholder: srcRect = an.find("floor_default")->second.FramePositions.front(); break;

			case MapTileTypes::Wall_Top: srcRect = an.find("wall_top")->second.FramePositions.front(); break;
			case MapTileTypes::Wall_Left: srcRect = an.find("wall_side")->second.FramePositions.front(); break;
			case MapTileTypes::Wall_Right: srcRect = an.find("wall_side")->second.FramePositions.front(); break;
			case MapTileTypes::Wall_Bottom: srcRect = an.find("wall_bottom")->second.FramePositions.front(); break;

			case MapTileTypes::Corner_Top_Left: srcRect = an.find("corner_top")->second.FramePositions.front(); break;
			case MapTileTypes::Corner_Top_Right: srcRect = an.find("corner_top")->second.FramePositions.front(); break;
			case MapTileTypes::Corner_Bottom_Left: srcRect = an.find("corner_bottom")->second.FramePositions.front(); break;
			case MapTileTypes::Corner_Bottom_Right: srcRect = an.find("corner_bottom")->second.FramePositions.front(); break;

			case MapTileTypes::Endblock_Top: srcRect = an.find("endblock_top")->second.FramePositions.front(); break;
			case MapTileTypes::Endblock_Left: srcRect = an.find("endblock_side")->second.FramePositions.front(); break;
			case MapTileTypes::Endblock_Right: srcRect = an.find("endblock_side")->second.FramePositions.front(); break;
			case MapTileTypes::Endblock_Bottom: srcRect = an.find("endblock_bottom")->second.FramePositions.front(); break;

			case MapTileTypes::Middle_Block_Horizontal: srcRect = an.find("middle_horizontal")->second.FramePositions.front(); break;
			case MapTileTypes::Middle_Block_Vertical: srcRect = an.find("middle_vertical")->second.FramePositions.front(); break;

			default: break;
			}

			// Map tile position based on row/column within the mapLayout
			auto tile = MapTile(renderPtr, texture, Vec2(column * 96.f, row * 96.f), Vec2(32.f, 32.f), srcRect, 0);
			engine->AddNewGameObject(std::make_unique<MapTile>(tile));
		}
	}
}
