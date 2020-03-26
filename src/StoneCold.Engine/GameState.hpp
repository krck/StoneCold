
#ifndef STONECOLD_GAMESTATE_H
#define STONECOLD_GAMESTATE_H

#include "Types.hpp"
#include "Entity.hpp"
#include "Settings.hpp"
#include "EngineCore.hpp"
#include "EventManager.hpp"
#include "TransformationSystem.hpp"
#include "ScreenPositionSystem.hpp"
#include "RenderSystem.hpp"

namespace StoneCold::Engine {

class GameState : public State {
public:
	GameState(uint16 maxEntities, SDL_Renderer* renderer, EngineCore* engine);
	GameState(const GameState&) = delete;
	GameState& operator=(const GameState&) = delete;

	virtual void Initialize() override;

	virtual bool HandleSDLEvent(const SDL_Event& sdlEvent) override { return false; }
	virtual void HandleInputEvent(const std::vector<uint8>& keyStates) override;
	virtual void Update(uint32 frameTime) override;
	virtual void Render() override;

	void SetSpawnPosition(Vec2i spawnPoint);
	void SetEntities(entityId player, const std::vector<entityId>& mapTiles);

	inline const std::vector<entityId>& GetMapTiles() { return _mapTiles; }

	~GameState() = default;

private:
	EventManager& _eventManager;
	SDL_FRect _camera;
	
	// EntityId's for fast access
	entityId _player;
	std::vector<entityId> _mapTiles;

	// System ptrs for fast access
	std::shared_ptr<TransformationSystem> _transformationSystem;
	std::shared_ptr<ScreenPositionSystem> _screenPositionSystem;
	std::shared_ptr<RenderSystem> _renderSystem;
};

}

#endif
