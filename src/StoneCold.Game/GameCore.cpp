
#include "GameCore.hpp"

#include "Data_Animations.hpp"

using namespace StoneCold::Game;
using namespace StoneCold::Resources;

bool GameCore::Initialize() {
	try {
		// Setup the Engine, which in turn will setup SDL and create the Window
		_engine.Initialize("StoneCold");
		auto rendererPtr = _engine.GetSDLRenderer();
		// Setup the ResouceManager and the GameResouces class and load the global Resources
		_resources.Initialize(rendererPtr);
		_gameResources.Initialize(&_resources);
		_gameResources.LoadGlobalResouces();


		auto playerTexture = _resources.GetResource<TextureResource>(PLAYER_TEXTURE);
		auto pc = PlayerCharacter(rendererPtr, playerTexture, playerAnimation, Vec2(), Vec2(34, 34), 3, 200);


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
