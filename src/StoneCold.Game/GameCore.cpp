
#include "GameCore.hpp"

using namespace StoneCold::Game;

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
		const auto path = "C:\\Users\\PeterUser\\Documents\\GitHub\\StoneCold\\assets\\test.png";
		SDL_Surface* tmpSurface = IMG_Load(path);
		auto x1 = SDL_GetError();
		tex = SDL_CreateTextureFromSurface(rendererPtr, tmpSurface);
		SDL_FreeSurface(tmpSurface);

		auto pc = PlayerCharacter(rendererPtr, tex, Vec2(), Vec2(78.0f, 60.0f), 1, 200);

		_engine.AddNewGameObject(std::make_unique<PlayerCharacter>(pc));

		return true;
	}
	catch (const std::exception & ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}
}

//
// Run the main EngineCore-loop
//
int GameCore::Run() {
	try {
		uint timeStamp_new = SDL_GetTicks();
		uint timeStamp_old = SDL_GetTicks();
		uint frameTime = 0; // delta in ms

		while (!SDL_QuitRequested()) {
			timeStamp_new = SDL_GetTicks();
			frameTime = timeStamp_new - timeStamp_old;

			// FPS Limiter (Nice, because it works without WAIT)
			if (frameTime > (1000.0f / FPS)) {
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
		}
		return 0;
	}
	catch (const std::exception & ex) {
		std::cout << ex.what() << std::endl;
		return -1;
	}
}
