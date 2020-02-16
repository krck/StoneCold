
#include "Game.hpp"

using namespace StoneCold;

Game::Game(std::string&& windowName) : _windowName(std::move(windowName)), _window(nullptr), _renderer(nullptr) {}
Game::Game(const std::string& windowName) : _windowName(windowName), _window(nullptr), _renderer(nullptr) {}

//
// Initializes the SDL Ressources and 
// creats/show the Application Window
//
bool Game::Initialize() {
	try {
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			throw GameException("SDL Error on init: " + std::string(SDL_GetError()));

		SetupWindow();
		SetupSDL();

		_player = std::make_unique<Entity>(_renderer.get(), BASE_PATH + "test.png", 90, 81);

		return true;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return false;
	}
}

//
// Create and Show the Application Window
//
void Game::SetupWindow() {
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
void Game::SetupSDL() {
	// Create the Renderer to draw within the Window (-1 for default Window driver)
	// Set only the SDL_RENDERER_ACCELERATED Flag and NO Vsync! (Managing Frame-Times is important)
	auto tmpRend = std::unique_ptr<SDL_Renderer, SDL_RendererDeleter>(SDL_CreateRenderer(_window.get(), -1, SDL_RENDERER_ACCELERATED));
	_renderer.swap(tmpRend);

	if (_renderer == nullptr)
		throw GameException("SDL Error on renderer creation: " + std::string(SDL_GetError()));
}

//
// Run the main game-loop
//
int Game::Run() {
	try {
		SDL_Event event;
		uint timeStamp_new = SDL_GetTicks(), timeStamp_old = SDL_GetTicks();
		while (!SDL_QuitRequested()) {
			// FPS Limiter (Nice, because it works without WAIT)
			timeStamp_new = SDL_GetTicks();
			if ((timeStamp_new - timeStamp_old) > (1000.0f / FPS)) {
				timeStamp_old = timeStamp_new;

				// Handle all Events in the queue
				while (SDL_PollEvent(&event)) {
					HandleEvent(event);
				}

				Update();
				Render();
			}
		}
		return 0;
	}
	catch (const std::exception& ex) {
		std::cout << ex.what() << std::endl;
		return -1;
	}
}

void Game::HandleEvent(const SDL_Event& event) {
	switch (event.type)
	{
	default:
		break;
	}
}

void Game::Update() {
	_player->Update();
}

void Game::Render() {
	// Clear the Frame (white)
	SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, 255);
	SDL_RenderClear(_renderer.get());

	_player->Render();

	// Render to the Window
	SDL_RenderPresent(_renderer.get());
}

//
// Cleanup all the SDL2 Ressources
// (Managed smart-pointers, because the order is important)
// 
Game::~Game() {
	_renderer.reset();
	_window.reset();
	SDL_Quit();
}
