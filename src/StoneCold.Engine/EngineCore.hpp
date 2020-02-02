
#ifndef STONECOLD_ENGINECORE_H
#define STONECOLD_ENGINECORE_H

#include "SimulationManager.hpp"
#include "Exception.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace StoneCold::Engine {

class EngineCore {
public:
	EngineCore(std::string&& appName);
	EngineCore(const std::string& appName);
	EngineCore(const EngineCore&) = delete;
	EngineCore& operator=(const EngineCore&) = delete;

	bool Initialize();
	int Run();

	~EngineCore();

private:
	void SetupWindow();
	void SetupSDL();

private:
	const std::string _windowName;
	std::unique_ptr<SDL_Window, SDL_WindowDeleter> _window;
	std::unique_ptr<SDL_Renderer, SDL_RendererDeleter> _renderer;
};

}

#endif
