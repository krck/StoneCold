
#include "GameCore.hpp"

using namespace StoneCold::Game;
using namespace StoneCold::Resources;


GameCore::GameCore()
	: _sdl(SDLManager())
	, _engine(EngineCore())
	, _eventManager(EventManager::GetInstance())
	, _resources(ResourceManager())
	, _simulation(SimulationManager()) { };


bool GameCore::Initialize(const std::string& windowName) {
	try {
		// Init SDL will create and show the Application Window
		if (_sdl.InitializeSDL(windowName)) {
			// Get the SDL_Renderer and setup the Engine
			auto rendererPtr = _sdl.GetSDLRenderer();
			_engine.Initialize(rendererPtr);
			// Setup all the additional Managers in the correct order
			_resources.Initialize(rendererPtr);
			_simulation.Initialize(&_engine, &_resources, rendererPtr);

			// Load all global Resources and create the basic States
			_simulation.CreateIntroState();
			_simulation.CreateGameState();
			_simulation.CreateMenuState();
			// Load a first Level and add it to the GameState
			_simulation.LoadLevel();

			// Push the first State to update and render
			auto firstState = _engine.GetState<IntroState>();
			_engine.PushState(firstState);

			return true;
		}
		else {
			return false;
		}
	}
	catch (const std::exception & ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}
}


//
// Run the main Game-loop
//
int GameCore::Run() {
	try {
		// Setup timing and loop variables
		bool exit = false;
		const uint frameLimit = (uint)truncf(1000.0f / FPS);
		uint timeStamp_new = SDL_GetTicks();
		uint timeStamp_old = SDL_GetTicks();
		uint frameTime = 0; // delta in ms

		// Setup Event-Handling variables
		uint userEventType = _eventManager.UserEventType;
		auto keyStates = std::vector<uint8>();
		int numKeys = 0;
		SDL_Event event;

		// Start the main loop
		while (!exit) {
			timeStamp_new = SDL_GetTicks();
			frameTime = timeStamp_new - timeStamp_old;

			// FPS Limiter (Source of the "micro studder"??)
			// Can go now anyway, because updates are delta-time based
			// if (frameTime > frameLimit) {}

			// Poll the event loop to gather events from input devices
			while (SDL_PollEvent(&event) != 0) {
				if (event.type == SDL_QUIT)
					exit = true;

				// Pass SDL Events on to the Engine/States and do nothing if it was handled there
				if (!_engine.HandleSDLEvent(event)) {
					// Handle the custom User-Events
					if (event.type == userEventType && event.user.code == EventCode::ChangeLevel) {
						// Load a new Level
						_simulation.LoadLevel();
					}
				}
			}

			// Get a snapshot of the current state of the keyboard and handle the input
			const uint8* keyPtr = SDL_GetKeyboardState(&numKeys);
			keyStates = std::vector<uint8>(keyPtr, keyPtr + numKeys);
			_engine.HandleInputEvent(keyStates);

			// Update and render all Entitys
			_engine.Update(frameTime);
			_engine.Render();

			timeStamp_old = timeStamp_new;
		}
		return 0;
	}
	catch (const std::exception & ex) {
		std::cout << ex.what() << std::endl;
		return -1;
	}
}
