
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

		auto pc = PlayerCharacter(rendererPtr, tex, Vec2i(), Vec2i(78, 60), 1, 3);

		_engine.AddNewGameObject(std::make_shared<PlayerCharacter>(pc));

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
		SDL_Event event;
		uint timeStamp_new = SDL_GetTicks(), timeStamp_old = SDL_GetTicks();

		while (!SDL_QuitRequested()) {
			// FPS Limiter (Nice, because it works without WAIT)
			timeStamp_new = SDL_GetTicks();
			if ((timeStamp_new - timeStamp_old) > (1000.0f / FPS)) {
				SDL_PollEvent(&event);

				_engine.HandleEvent(event);
				_engine.Update(timeStamp_old, timeStamp_new);
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
