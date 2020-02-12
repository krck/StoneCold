
#include "GameCore.hpp"

using namespace StoneCold::Game;

// THIS MUST GO
SDL_Texture* tex = nullptr;

auto playerAnimations = std::unordered_map<std::string, Animation>({
	{"idle", ({ {0,0,34,34}, {34,0,34,34}, {68,0,34,34}, {102,0,34,34}, {136,0,34,34} }) },
	{"walk", ({ {0,34,34,34}, {34,34,34,34}, {68,34,34,34}, {102,34,34,34}, {136,34,34,34}, {170,34,34,34}, {204,34,34,34}, {238,34,34,34} }) },
	{"atk2", ({ {0,68,34,34}, {34,68,34,34}, {68,68,34,34}, {102,68,34,34}, {136,68,34,34}, {170,68,34,34}, {204,68,34,34} }) },
	{"atk1", ({ {0,102,34,34}, {34,102,34,34}, {68,102,34,34}, {102,102,34,34}, {136,102,34,34}, {170,102,34,34} }) },
	{"atk3", ({ {0,136,34,34}, {34,136,34,34} }) },
	{"jump", ({ {0,170,34,34}, {34,170,34,34}, {68,170,34,34}, {102,170,34,34}, {136,170,34,34} }) },
	{"hurt", ({ {0,204,34,34}, {34,204,34,34}, {68,204,34,34}, {102,204,34,34} }) },
	{"dead", ({ {0,238,34,34}, {34,238,34,34}, {68,238,34,34}, {102,238,34,34}, {136,238,34,34}, {170,238,34,34}, {204,238,34,34} }) }
});

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

		auto pc = PlayerCharacter(rendererPtr, tex, playerAnimations, Vec2(), Vec2(78.0f, 60.0f), 1, 200);

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
		const uint frameLimit = truncf(1000.0f / FPS);
		uint timeStamp_new = SDL_GetTicks();
		uint timeStamp_old = SDL_GetTicks();
		uint frameTime = 0; // delta in ms

		while (!SDL_QuitRequested()) {
			timeStamp_new = SDL_GetTicks();
			frameTime = timeStamp_new - timeStamp_old;

			// FPS Limiter (Source of the micro-studder)
			// This can go now, because updates are delta-time based
			//if (frameTime > frameLimit) { do everythin here }
			
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
	catch (const std::exception & ex) {
		std::cout << ex.what() << std::endl;
		return -1;
	}
}
