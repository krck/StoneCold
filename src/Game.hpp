
#ifndef STONECOLD_GAME_H
#define STONECOLD_GAME_H

#include "Entity.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace StoneCold {

class Game {
public:
	Game(std::string&& appName);
	Game(const std::string& appName);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	bool Initialize();
	int Run();

	~Game();

private:
	void SetupWindow();
	void SetupSDL();

	void HandleEvent(const SDL_Event& event);
	void Update();
	void Render();

private:
	const std::string _windowName;
	std::unique_ptr<SDL_Window, SDL_WindowDeleter> _window;
	std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> _renderer;

	std::unique_ptr<Entity> _player;
};

}

#endif
