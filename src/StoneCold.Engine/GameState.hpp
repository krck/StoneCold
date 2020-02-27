
#ifndef STONECOLD_GAMESTATE_H
#define STONECOLD_GAMESTATE_H

#include "Types.hpp"
#include "Settings.hpp"
#include "EngineCore.hpp"
#include "EventManager.hpp"
#include "TransformComponent.hpp"
#include "CollisionManager.hpp"

namespace StoneCold::Engine {

class GameState : public State {
public:
	GameState(EngineCore* engine);
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;

	virtual bool HandleSDLEvent(const SDL_Event& sdlEvent) override { return false; }
	virtual void HandleInputEvent(const std::vector<uint8>& keyStates) override;
	virtual void Update(uint frameTime) override;
	virtual void Render() override;

	void SetPlayer(std::unique_ptr<GameObject>&& playerObject);
	void SetLevel(std::vector<std::shared_ptr<GameObject>>&& mapObjects, std::vector<std::shared_ptr<GameObject>>&& gameObjects, Vec2i spawnPoint);
	void SetGUI(std::vector<std::shared_ptr<GameObject>>&& guiObjects);

	~GameState() = default;

private:
	EventManager& _eventManager;
	CollisionManager _collisionManager;
	SDL_FRect _camera;

	//
	// Pointers to the Players GameObject for fast access
	//
	std::unique_ptr<GameObject> _player;
	TransformComponent* _playerTransformation;

	//
	// unordered_maps with all GameObjects (Player, NPCs, MapTiles, ...)
	// Each map has a TextureResource hash as key to batch render by Texture
	//
	std::unordered_map<hash64, std::vector<std::shared_ptr<GameObject>>> _mapObjects;
	std::unordered_map<hash64, std::vector<std::shared_ptr<GameObject>>> _gameObjects;
	std::vector<std::shared_ptr<GameObject>> _guiObjects;

	//
	// Based on the GameObject maps, this stores a pointer
	// to each GameObject, that has a CollisionComponent
	//
	std::vector<CollisionComponent*> _collidableObjects;

};

}

#endif
