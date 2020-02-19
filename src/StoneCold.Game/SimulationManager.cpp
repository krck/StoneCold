
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

void SimulationManager::LoadLevelResouces(LevelType type) {
	try {
		// First clear the Level Resources
		_resourceManager->UnloadResources(ResourceLifeTime::Level);

		// Animation data is the same for all Maps. Only Textures need to loaded by LevelType
		_resourceManager->LoadResource<AnimationResource>(ResourceLifeTime::Level, MAP_ANIMATION);
		if (type == LevelType::Grassland) {
			_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, GRASSLAND_TEXTURE);
		}

		// Get a new, randomly generated Map
		auto mapData = _engine->GetNewMap();
		auto animation = _resourceManager->GetResource<AnimationResource>(MAP_ANIMATION);
		auto texture = _resourceManager->GetResource<TextureResource>(GRASSLAND_TEXTURE);
		auto renderPtr = _engine->GetSDLRenderer();
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
				case MapTileTypes::Wall_Right: srcRect = an.find("wall_side")->second.FramePositions.front(); flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL; break;
				case MapTileTypes::Wall_Bottom: srcRect = an.find("wall_bottom")->second.FramePositions.front(); break;

				case MapTileTypes::Corner_Top_Left: srcRect = an.find("corner_top")->second.FramePositions.front();  flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL; break;
				case MapTileTypes::Corner_Top_Right: srcRect = an.find("corner_top")->second.FramePositions.front(); break;
				case MapTileTypes::Corner_Bottom_Left: srcRect = an.find("corner_bottom")->second.FramePositions.front();  flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL; break;
				case MapTileTypes::Corner_Bottom_Right: srcRect = an.find("corner_bottom")->second.FramePositions.front(); break;

				case MapTileTypes::Endblock_Top: srcRect = an.find("endblock_top")->second.FramePositions.front(); break;
				case MapTileTypes::Endblock_Left: srcRect = an.find("endblock_side")->second.FramePositions.front(); flip = SDL_RendererFlip::SDL_FLIP_HORIZONTAL; break;
				case MapTileTypes::Endblock_Right: srcRect = an.find("endblock_side")->second.FramePositions.front(); break;
				case MapTileTypes::Endblock_Bottom: srcRect = an.find("endblock_bottom")->second.FramePositions.front(); break;

				case MapTileTypes::Middle_Block_Horizontal: srcRect = an.find("middle_horizontal")->second.FramePositions.front(); break;
				case MapTileTypes::Middle_Block_Vertical: srcRect = an.find("middle_vertical")->second.FramePositions.front(); break;

				default: break;
				}

				// Map tile position based on row/column within the mapLayout
				auto tile = MapTile(renderPtr, texture, Vec2(column * 96.f, row * 96.f), Vec2(32.f, 32.f), srcRect, flip, 0);
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
