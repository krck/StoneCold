
#include "GameCore.hpp"

using namespace StoneCold::Game;
using namespace StoneCold::Resources;

bool GameCore::Initialize() {
	try {
		// Setup the Engine, which in turn will setup SDL and create the Window
		_engine.Initialize("StoneCold");
		auto rendererPtr = _engine.GetSDLRenderer();
		// Setup all the Managers in the correct order
		_resources.Initialize(rendererPtr);
		_simulationManager.Initialize(&_engine, &_resources);

		// Load the Global Resources, create the PlayerCharacter and add it to the render list
		_simulationManager.LoadGlobalResouces();
		_simulationManager.LoadLevelResouces();

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
		bool exit = false;
		const uint frameLimit = (uint)truncf(1000.0f / FPS);
		uint timeStamp_new = SDL_GetTicks();
		uint timeStamp_old = SDL_GetTicks();
		uint frameTime = 0; // delta in ms
        SDL_Event event;

		while (!exit) {
			timeStamp_new = SDL_GetTicks();
			frameTime = timeStamp_new - timeStamp_old;

			// FPS Limiter (Source of the micro-studder)
			// This can go now, because updates are delta-time based
			// if (frameTime > frameLimit) {}

            // Poll the event loop to gather events from input devices
            while (SDL_PollEvent(&event) != 0) { 
				if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F5)
					_simulationManager.LoadLevelResouces();
				if (event.type == SDL_QUIT) 
					exit = true;
			}

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
