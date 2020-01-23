
#include "EngineCore.hpp"

using namespace StoneCold;

EngineCore::EngineCore(std::string&& windowName) : _windowName(std::move(windowName)), _window(nullptr), _renderer(nullptr) {}
EngineCore::EngineCore(const std::string& windowName) : _windowName(windowName), _window(nullptr), _renderer(nullptr) {}

//
// Initializes the SDL Ressources and 
// creats/show the EngineCore Window
//
bool EngineCore::Initialize() {
	try {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw GameException("SDL Error on init: " + std::string(SDL_GetError()));

		SetupWindow();
		SetupSDL();

		return true;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}
}

//
// Create and Show the EngineCore Window
//
void EngineCore::SetupWindow() {
	// Create and Show the main Window
	const uint pos = SDL_WINDOWPOS_CENTERED;
	const uint flags = 0;

	auto tmpWin = std::unique_ptr<SDL_Window, SDL_WindowDeleter>(SDL_CreateWindow(_windowName.c_str(), pos, pos, WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT, flags));
	_window.swap(tmpWin);

	// Set the min. Window size, if creation was successful 
	if (_window != nullptr)
		SDL_SetWindowMinimumSize(_window.get(), WINDOW_SIZE_WIDTH, WINDOW_SIZE_HEIGHT);
	else
		throw GameException("SDL Error on window creation: " + std::string(SDL_GetError()));
}

//
// Create the SDL2 Renderer and a background Texture
//
void EngineCore::SetupSDL() {
	// Create the Renderer to draw within the Window (-1 for default Window driver)
	// Set only the SDL_RENDERER_ACCELERATED Flag and NO Vsync! (Managing Frame-Times is important)
	auto tmpRend = std::unique_ptr<SDL_Renderer, SDL_RendererDeleter>(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED));
	_renderer.swap(tmpRend);

	if (_renderer == nullptr)
		throw GameException("SDL Error on renderer creation: " + std::string(SDL_GetError()));
}

//
// Run the main EngineCore-loop
//
int EngineCore::Run() {
	try {
		SDL_Event event;
		ResourceManager resourceManager;
		auto gameManager(GameManager(_renderer.get(), resourceManager));
		uint timeStamp_new = SDL_GetTicks(), timeStamp_old = SDL_GetTicks();

		while (!SDL_QuitRequested()) {
			// FPS Limiter (Nice, because it works without WAIT)
			timeStamp_new = SDL_GetTicks();
			if ((timeStamp_new - timeStamp_old) > (1000.0f / FPS)) {
				SDL_PollEvent(&event);
				gameManager.HandleEvent(event);
				gameManager.Update(timeStamp_old, timeStamp_new);
				gameManager.Render();

				timeStamp_old = timeStamp_new;
			}
		}
		return 0;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return -1;
	}
}

//
// Cleanup all the SDL2 Ressources
// (Managed smart-pointers, because the order is important)
// 
EngineCore::~EngineCore() {
	_renderer.reset();
	_window.reset();
	SDL_Quit();
}
