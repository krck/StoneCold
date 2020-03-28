
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

		// Create a new IntroState
		auto intro = std::make_shared<IntroState>(20, _renderer, _engine);
		auto introECS = intro->GetECS();
		auto guiObjects = std::vector<std::unique_ptr<Entity>>();

		// Get all basic Resources needed by the IntroState (Background image, Font, ...)
		auto backgroundTexture = _resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Intro, BACKGROUND_IMAGE);
		auto fontTTF = _resourceManager->LoadResource<FontResource>(ResourceLifeTime::Intro, FONT_CROM);
		// ...

		// Create all basic Entities from the Resources, needed by the IntroState
		// Background Image
		SDL_Rect backgroundDimensions = { 0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT };
		SDL_FRect backgroundDimensionsF = { 0.f, 0.f, static_cast<float>(WINDOW_SIZE_WIDTH), static_cast<float>(WINDOW_SIZE_HEIGHT) };
		auto background = Background(introECS, backgroundTexture, backgroundDimensions, backgroundDimensionsF);
		// Label "Press any Button"
		const std::string labelText = "Press any Button to start ...";
		auto lbTex = _resourceManager->LoadFontTexture(ResourceLifeTime::Intro, "Label_Intro_Press_Any_Button", fontTTF->GetFontBig(), labelText, CL_BLACK);
		SDL_FRect dest = { (WINDOW_SIZE_WIDTH / 2.f) - (lbTex->SurfaceSize.X / 2.f), 500.f, static_cast<float>(lbTex->SurfaceSize.X), static_cast<float>(lbTex->SurfaceSize.Y) };
		auto guiLabel = Label(introECS, lbTex, lbTex->SurfaceSize, dest);
		guiObjects.push_back(std::make_unique<Entity>(guiLabel));

		// Finally add the new IntroState to the Engines States
		_engine->AddState<IntroState>(intro);
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

		// Create a new GameState
		auto game = std::make_shared<GameState>(5000, _renderer, _engine);
		auto gameECS = game->GetECS();
		game->Initialize();

		// Get all basic Resources needed by the GameState (Player Character, Player GUI, etc.)
		_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Game, PLAYER_TEXTURE);
		_resourceManager->LoadResource<AnimationResource>(ResourceLifeTime::Game, PLAYER_ANIMATION);
		// ...

		// Create all basic Entitys from the Resources, needed by the GameState
		auto playerTexture = _resourceManager->GetResource<TextureResource>(PLAYER_TEXTURE);
		auto playerAnimation = _resourceManager->GetResource<AnimationResource>(PLAYER_ANIMATION);
		auto player = PlayerCharacter(gameECS, playerTexture, playerAnimation, Vec2(), Vec2(32, 32), 3, 250);
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

		// Create a new MenuState
		auto menu = std::make_shared<MenuState>(50, _renderer, _engine);
		auto menuECS = menu->GetECS();
		auto guiObjects = std::vector<std::unique_ptr<Entity>>();

		// Get all basic Resources needed by the MenuState (Background image, Font, ...)
		auto backgroundTexture = _resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Menu, BACKGROUND_IMAGE);
		auto stonecoldTexture = _resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Menu, STONECOLD_LOGO);
		auto buttonAnimation = _resourceManager->LoadResource<AnimationResource>(ResourceLifeTime::Menu, BUTTON_ANIMATION);
		auto guiTexture = _resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Menu, GUI_TEXTURE);
		auto fontTTF = _resourceManager->LoadResource<FontResource>(ResourceLifeTime::Menu, FONT_CROM);
		// ...

		// Create all basic Entitys from the Resources, needed by the MenuState
		// Background Image
		SDL_Rect backgroundDimensions = { 0, 0, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT };
		SDL_FRect backgroundDimensionsF = { 0.f, 0.f, static_cast<float>(WINDOW_SIZE_WIDTH), static_cast<float>(WINDOW_SIZE_HEIGHT) };
		auto background = Background(menuECS, backgroundTexture, backgroundDimensions, backgroundDimensionsF);
		// StoneCold Logo
		SDL_Rect logoDimensions = { 0, 0, stonecoldTexture->SurfaceSize.X, stonecoldTexture->SurfaceSize.Y };
		SDL_FRect logoDimensionsF = { (WINDOW_SIZE_WIDTH / 2.f) - 250.f, 100.f, 500.f, 100.f };
		guiObjects.push_back(std::make_unique<Entity>(Background(menuECS, stonecoldTexture, logoDimensions, logoDimensionsF)));
		// Button "Play"
		auto btnContentPlay = _resourceManager->LoadFontTexture(ResourceLifeTime::Menu, "Button_Menu_Start", fontTTF->GetFontBig(), "Play", CL_BLACK);
		SDL_FRect destPlay = { (WINDOW_SIZE_WIDTH / 2.f) - 100.f, 300.f, 200.f, 50.f };
		guiObjects.push_back(std::make_unique<Entity>(Button(menuECS, guiTexture, btnContentPlay, buttonAnimation, destPlay, btnContentPlay->SurfaceSize)));
		// Button "Options"
		auto btnContentOptions = _resourceManager->LoadFontTexture(ResourceLifeTime::Menu, "Button_Menu_Options", fontTTF->GetFontBig(), "Options", CL_BLACK);
		SDL_FRect destOptions = { (WINDOW_SIZE_WIDTH / 2.f) - 100.f, 370.f, 200.f, 50.f };
		guiObjects.push_back(std::make_unique<Entity>(Button(menuECS, guiTexture, btnContentOptions, buttonAnimation, destOptions, btnContentOptions->SurfaceSize)));
		// Button "Credits"
		auto btnContentCredits = _resourceManager->LoadFontTexture(ResourceLifeTime::Menu, "Button_Menu_Credits", fontTTF->GetFontBig(), "Credits", CL_BLACK);
		SDL_FRect destCredits = { (WINDOW_SIZE_WIDTH / 2.f) - 100.f, 440.f, 200.f, 50.f };
		guiObjects.push_back(std::make_unique<Entity>(Button(menuECS, guiTexture, btnContentCredits, buttonAnimation, destCredits, btnContentCredits->SurfaceSize)));
		// Button "Quit"
		auto btnContentQuit = _resourceManager->LoadFontTexture(ResourceLifeTime::Menu, "Button_Menu_Quit", fontTTF->GetFontBig(), "Quit", CL_BLACK);
		SDL_FRect destQuit = { (WINDOW_SIZE_WIDTH / 2.f) - 100.f, 510.f, 200.f, 50.f };
		guiObjects.push_back(std::make_unique<Entity>(Button(menuECS, guiTexture, btnContentQuit, buttonAnimation, destQuit, btnContentQuit->SurfaceSize)));

		// Finally add the new MenuState to the Engines States
		_engine->AddState<MenuState>(menu);
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
			auto gameState = _engine->GetState<GameState>();
			auto gameECS = gameState->GetECS();

			// Get a new, randomly generated Map Texture
			const auto levelType = (LevelType)(rand() % 5 + 0);
			std::string texturePath = MAP_TEXTURES.find(levelType)->second;
			_resourceManager->LoadResource<TextureResource>(ResourceLifeTime::Level, texturePath);

			// Pre-defined map patterns
			std::pair<float, float> pattern = { 0.f, 0.f };
			const std::vector<std::pair<float, float>> mapPatterns = {
				{ 0.6f, 0.01f }, // 1) ROCKY: Map with few open spaces, very jagged edges and lots of corridors and obstacles
				{ 0.75f, 0.1f }, // 2) MIXED: Map with bigger open spaces, some jagged edges and few obstacles
				{ 0.95f, 0.2f }	 // 3) FLAT: Map with one massive, open space, smoothe-ish edges and no corridors/obstacles
			};

			// Grassland and Arctic can be FLAT or MIXED
			if (levelType == LevelType::Grassland || levelType == LevelType::Arctic) { pattern = mapPatterns[(rand() & 1) + 1]; }
			// Highlands or Desert can be ROCKY or MIXED
			else if (levelType == LevelType::Highlands || levelType == LevelType::Desert) { pattern = mapPatterns[(rand() & 1)]; }
			// Castle can only be ROCKY (default)
			else { pattern = mapPatterns[0]; }

			// Get a new, randomly generated Map Layout
			auto mapLayout = _mapManager.GenerateMap(Vec2i(70, 70), pattern.first, pattern.second);
			auto spawnPos = _mapManager.GetStartEndPositions().first;
			auto texture = _resourceManager->GetResource<TextureResource>(texturePath);

			// Create the actual MapTiles, based on the Layout and the loaded MapTexture
			auto mapObjects = std::vector<std::shared_ptr<Entity>>();
			for (uint64 row = 0; row < mapLayout.size(); row++) {
				for (uint64 column = 0; column < mapLayout[row].size(); column++) {
					// Map tile position based on row/column within the mapLayout
					const auto type = mapFrames.find(mapLayout[row][column]);
					const auto frame = type->second;

					// Set the Source rectange frame inside the texture (Pixels to take, from the .png)
					SDL_Rect src = frame.first;
					// Set the Destination rectangle with the actual position on screen with scaling (Where to put the Pixels)
					SDL_FRect dest = { column * 96.f, row * 96.f, static_cast<float>(src.w * 3), static_cast<float>(src.h * 3) };

					auto mapTileEntity = gameECS->CreateEntity();
					gameECS->AddComponent<ScreenPositionComponent>(mapTileEntity, { src, dest });
					gameECS->AddComponent<SpriteComponent>(mapTileEntity, { texture->GetTextureSDL(), frame.second });
					// Add the CollisionComponent in case its a Wall-Tile
					if (static_cast<int>(type->first) > static_cast<int>(MapTileTypes::Floor_Shadow))
						gameECS->AddComponent<CollisionComponent>(mapTileEntity, { "wall", Vec2(), dest, nullptr, true });
				}
			}

			// ...

			// Finally update the Engines GameState with the newly created Level
			gameState->SetLevel(std::move(mapObjects), std::vector<std::shared_ptr<Entity>>(), { spawnPos.X * 96, spawnPos.Y * 96 });
		}
	}
	catch (const std::exception & ex) {
		std::cout << "Loading the Game failed:\n" << ex.what() << std::endl;
	}
}
