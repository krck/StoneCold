
#include "SDLManager.hpp"

using namespace StoneCold::Engine;

//
// Initializes the SDL Ressources and 
// creats/show the EngineCore Window
//
bool SDLManager::InitializeSDL(const std::string& windowName) {
	try {
		_windowName = windowName;

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
void SDLManager::SetupWindow() {
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
void SDLManager::SetupSDL() {
	// Create the Renderer to draw within the Window (-1 for default Window driver)
	// Set only the SDL_RENDERER_ACCELERATED Flag and NO Vsync! (Managing Frame-Times is important)
	auto tmpRend = std::unique_ptr<SDL_Renderer, SDL_RendererDeleter>(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED));
	_renderer.swap(tmpRend);

	if (_renderer == nullptr)
		throw GameException("SDL Error on renderer creation: " + std::string(SDL_GetError()));
}

//
// Cleanup all the SDL2 Ressources
// (Managed smart-pointers, because the order is important)
// 
SDLManager::~SDLManager() {
	_renderer.reset();
	_window.reset();
	SDL_Quit();
}
