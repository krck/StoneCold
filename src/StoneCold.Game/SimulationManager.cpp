
#include "SimulationManager.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;
using namespace StoneCold::Resources;
using namespace StoneCold::Game;


bool StoneCold::Game::SimulationManager::Initialize(EngineCore* engine, ResourceManager* resourceManager, SDL_Renderer* renderer) {
	if (engine != nullptr && resourceManager != nullptr && renderer != nullptr) {
		_engine = engine;
		_resourceManager = resourceManager;
		_renderer = renderer;
		return true;
	}
	else {
		return false;
	}
}


void SimulationManager::CreateIntroState() {
	try {
		// First clear the Intro Resources
		_resourceManager->UnloadResources(ResourceLifeTime::Intro);
		_engine->ClearState<IntroState>();

		// Create a new IntroState;
		auto into = std::make_shared<IntroState>(_engine);

		// Load all basic Resources needed by the IntroState (Background image, ...)
		_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Intro, BACKGROUND_IMAGE);
		// ...

		// Create all basic Entitys from the Resources, needed by the IntroState
		auto backgroundTexture = _resourceManager->GetResource<TextureResource>(BACKGROUND_IMAGE);
		SDL_Rect backgroundDimensions = { 0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT };
		SDL_FRect backgroundDimensionsF = { 0.f, 0.f, static_cast<float>(WINDOW_SIZE_WIDTH), static_cast<float>(WINDOW_SIZE_HEIGHT) };
		auto background = Background(_renderer, backgroundTexture, backgroundDimensions, backgroundDimensionsF);
		into->SetBackground(std::make_unique<Background>(background));

		// Finally add the new IntroState to the Engines States
		_engine->AddState<IntroState>(into);
	}
	catch (const std::exception & ex) {
		std::cout << "Loading the Intro failed:\n" << ex.what() << std::endl;
	}
}


void SimulationManager::CreateGameState() {
	try {
		// First clear the Game Resources
		_resourceManager->UnloadResources(ResourceLifeTime::Game);
		_engine->ClearState<GameState>();

		// Create a new GameState;
		auto game = std::make_shared<GameState>(_engine);

		// Load all basic Resources needed by the GameState (Player Character, Player GUI, etc.)
		_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Game, PLAYER_TEXTURE);
		_resourceManager->LoadResource<AnimationResource>(ResourceLifeTime::Game, PLAYER_ANIMATION);
		// ...

		// Create all basic Entitys from the Resources, needed by the GameState
		auto playerTexture = _resourceManager->GetResource<TextureResource>(PLAYER_TEXTURE);
		auto playerAnimation = _resourceManager->GetResource<AnimationResource>(PLAYER_ANIMATION);
		auto player = PlayerCharacter(_renderer, playerTexture, playerAnimation, Vec2(), Vec2(32, 32), 3, 200);
		game->SetPlayer(std::make_unique<PlayerCharacter>(player));
		// ...

		// Finally add the new GameState to the Engines States
		_engine->AddState<GameState>(game);
	}
	catch (const std::exception & ex) {
		std::cout << "Loading the Game failed:\n" << ex.what() << std::endl;
	}
}


void SimulationManager::CreateMenuState() {
	try {
		// First clear the Menu Resources
		_resourceManager->UnloadResources(ResourceLifeTime::Menu);
		_engine->ClearState<MenuState>();

	}
	catch (const std::exception & ex) {
		std::cout << "Loading the Menu failed:\n" << ex.what() << std::endl;
	}
}


void SimulationManager::LoadLevel() {
	try {
		// First clear the Level Resources and check, if the Engine has a GameState that runs the Level
		_resourceManager->UnloadResources(ResourceLifeTime::Level);
		if (_engine->HasState<GameState>()) {
			// Get a new, randomly generated Map Texture
			auto levelType = (LevelType)(rand() % 5 + 0);
			std::string texturePath = MAP_TEXTURES.find(levelType)->second;
			_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, texturePath);

			// Get a new, randomly generated Map Layout
			auto mapLayout = _mapManager.GenerateMap(Vec2i(60, 60));
			auto spawnPos = _mapManager.GetStartEndPositions().first;
			auto texture = _resourceManager->GetResource<TextureResource>(texturePath);

			// Create the actual MapTiles, based on the Layout and the loaded MapTexture
			auto mapObjects = std::vector<std::shared_ptr<Entity>>();
			for (int row = 0; row < mapLayout.size(); row++) {
				for (int column = 0; column < mapLayout[row].size(); column++) {
					// Map tile position based on row/column within the mapLayout
					const auto type = mapFrames.find(mapLayout[row][column]);
					const auto frame = type->second;
					auto tile = MapTile(_renderer, texture, frame.first, Vec2(column * 96.f, row * 96.f), 3, frame.second, type->first);
					mapObjects.push_back(std::make_shared<MapTile>(tile));
				}
			}

			// ...

			// Finally update the Engines GameState with the newly created Level
			auto gameState = _engine->GetState<GameState>();
			gameState->SetLevel(std::move(mapObjects), std::vector<std::shared_ptr<Entity>>(), { spawnPos.X * 96, spawnPos.Y * 96 });
		}
	}
	catch (const std::exception & ex) {
		std::cout << "Loading the Game failed:\n" << ex.what() << std::endl;
	}
}
