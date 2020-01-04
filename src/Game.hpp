
#ifndef STONECOLD_GAME_H
#define STONECOLD_GAME_H

#include "TextureManager.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace StoneCold {

class Game {
public:
	Game(std::string&& appName, std::string&& resourcePath);
	Game(const std::string& appName, const std::string& resourcePath);
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
	const std::string _resourcePath;
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	SDL_Rect _playerDest;
	std::shared_ptr<SDL_Texture> _playerTex;
};

}

#endif
