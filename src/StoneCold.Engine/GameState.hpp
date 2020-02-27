
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

	void SetPlayer(std::unique_ptr<Entity>&& playerObject);
	void SetLevel(std::vector<std::shared_ptr<Entity>>&& mapObjects, std::vector<std::shared_ptr<Entity>>&& gameObjects, Vec2i spawnPoint);
	void SetGUI(std::vector<std::shared_ptr<Entity>>&& guiObjects);

	~GameState() = default;

private:
	EventManager& _eventManager;
	CollisionManager _collisionManager;
	SDL_FRect _camera;

	//
	// Pointers to the Players Entity for fast access
	//
	std::unique_ptr<Entity> _player;
	TransformComponent* _playerTransformation;

	//
	// unordered_maps with all Entitys (Player, NPCs, MapTiles, ...)
	// Each map has a TextureResource hash as key to batch render by Texture
	//
	std::unordered_map<hash64, std::vector<std::shared_ptr<Entity>>> _mapObjects;
	std::unordered_map<hash64, std::vector<std::shared_ptr<Entity>>> _gameObjects;
	std::vector<std::shared_ptr<Entity>> _guiObjects;

	//
	// Based on the Entity maps, this stores a pointer
	// to each Entity, that has a CollisionComponent
	//
	std::vector<CollisionComponent*> _collidableObjects;

};

}

#endif
