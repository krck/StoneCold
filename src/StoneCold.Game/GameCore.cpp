
#include "GameCore.hpp"

#include "Data_Animations.hpp"

using namespace StoneCold::Game;
using namespace StoneCold::Resources;

//class GameCore {
//
//private:
//	RessourceManager _ressourceManager;
//	GameResources _gameResources;
//	
//public:
//	void Init() {
//		// ... init enginge, ....
//		// ... init resourcemanager ....
//		_gameResources = GameResources(&_resourceManager);
//		
//		_gameResources.LoadGlobalResouces();
//		_gameResources.LoadLevelResouces(Level1);
//		
//		// ...
//		
//		gameObjects.add<Player>(RessourceManager.GetResource<TextureResource>("player")
//				       ,RessourceManager.GetResource<AnimationResource>("player")
//				       , ...)
//		
//		// ...
//	}
//	
//};

// THIS MUST GO
SDL_Texture* tex = nullptr;



bool GameCore::Initialize() {
	try {
		// Setup the Engine, which in turn will setup SDL and create the Window
		_engine.Initialize("StoneCold");
		auto rendererPtr = _engine.GetSDLRenderer();

		// INIT RESOURCE MANAGER AND RESOURCES HERE
		// _resources.gettexture ...
		// get renderer from engine
		const auto path = "C:\\Users\\PeterUser\\Documents\\GitHub\\StoneCold\\assets\\Dwarf_Sprite.png";
		SDL_Surface* tmpSurface = IMG_Load(path);
		auto x1 = SDL_GetError();
		tex = SDL_CreateTextureFromSurface(rendererPtr, tmpSurface);
		SDL_FreeSurface(tmpSurface);

		auto pc = PlayerCharacter(rendererPtr, tex, playerAnimation, Vec2(), Vec2(34, 34), 3, 200);

		_engine.AddNewGameObject(std::make_unique<PlayerCharacter>(pc));

		return true;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}
}

//
// Run the main EngineCore-loop
//
int GameCore::Run() {
	try {
		const uint frameLimit = truncf(1000.0f / FPS);
		uint timeStamp_new = SDL_GetTicks();
		uint timeStamp_old = SDL_GetTicks();
		uint frameTime = 0; // delta in ms

		while (!SDL_QuitRequested()) {
			timeStamp_new = SDL_GetTicks();
			frameTime = timeStamp_new - timeStamp_old;

			// FPS Limiter (Source of the micro-studder)
			// This can go now, because updates are delta-time based
			if (frameTime > frameLimit) {}

			// Pump the event loop to gather events from input devices
			SDL_PumpEvents();

			// Get a snapshot of the current state of the keyboard and handle the input
			const uint8* keyStates = SDL_GetKeyboardState(NULL);
			_engine.HandleEvent(keyStates);

			// Update and render all GameObjects
			_engine.Update(frameTime);
			_engine.Render();

			timeStamp_old = timeStamp_new;
		}
		return 0;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return -1;
	}
}
