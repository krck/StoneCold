
#ifndef STONECOLD_ENGINECORE_H
#define STONECOLD_ENGINECORE_H

#include "SDLManager.hpp"
#include "Exception.hpp"
#include "Component.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace StoneCold::Engine {

class EngineCore {
public:
	EngineCore() : _sdlManager(SDLManager()), _renderer(nullptr), _gameObjects(std::vector<std::shared_ptr<GameObject>>()) { };
	EngineCore(const EngineCore&) = delete;
	EngineCore& operator=(const EngineCore&) = delete;

	inline SDL_Renderer* GetSDLRenderer() { return _renderer; }

	bool Initialize(const std::string& windowName);
	void HandleEvent(const SDL_Event& event);
	void Update(uint timestampOld, uint timestampNew);
	void Render();

	void AddNewGameObject(std::shared_ptr<GameObject>&& gameObject);

	~EngineCore() = default;

private:
	SDLManager _sdlManager;
	SDL_Renderer* _renderer;

	//
	// Vector with all GameObjects (Player, NPCs, MapTiles, ...)
	// that need to be updated and rendered in every loop iteration
	//
	// Group (and render) this by SDL_Texture for better performance
	//
	std::vector<std::shared_ptr<GameObject>> _gameObjects;
};

}

#endif
