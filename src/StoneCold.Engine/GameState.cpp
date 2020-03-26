
#include "GameState.hpp"

using namespace StoneCold;
using namespace StoneCold::Engine;

GameState::GameState(uint16 maxEntities, SDL_Renderer* renderer, EngineCore* engine)
	: State(maxEntities, renderer, engine)
	, _eventManager(EventManager::GetInstance())
	, _mapTiles(std::vector<entityId>())
	, _transformationSystem(nullptr)
	, _screenPositionSystem(nullptr)
	, _renderSystem(nullptr)
	, _player(0)
	, _camera({ 0.f, 0.f, (float)WINDOW_SIZE_WIDTH, (float)WINDOW_SIZE_HEIGHT }) { }


void GameState::Initialize() {
	auto transArrayPtr = _ecs.GetComponentArray<TransformationComponent>();
	auto velArrayPtr = _ecs.GetComponentArray<VelocityComponent>();
	auto posArrayPtr = _ecs.GetComponentArray<ScreenPositionComponent>();
	auto sprArrayPtr = _ecs.GetComponentArray<SpriteComponent>();

	// Create and add the Transformation System
	_transformationSystem = std::make_shared<TransformationSystem>(*transArrayPtr, *velArrayPtr);
	_ecs.AddSystem<TransformationSystem>(_transformationSystem);
	// Create and add the Screen-Position System
	_screenPositionSystem = std::make_shared<ScreenPositionSystem>(*transArrayPtr, *posArrayPtr);
	_ecs.AddSystem<ScreenPositionSystem>(_screenPositionSystem);
	// Create and add the Render System
	_renderSystem = std::make_shared<RenderSystem>(_renderer, *posArrayPtr, *sprArrayPtr);
	_ecs.AddSystem<RenderSystem>(_renderSystem);
	// ...
}


void GameState::HandleInputEvent(const std::vector<uint8>& keyStates) {
	// In case F5 was pressed: Trigger Level-Refresh
	if (keyStates[SDL_SCANCODE_F5]) {
		_eventManager.PublishEvent(EventCode::ChangeLevel);
	}
	// Handle the Player input
	else {
		// Get the player components
		auto& a = _ecs.GetComponentArray<AnimationComponent>()->at(_player);
		auto& t = _ecs.GetComponentArray<TransformationComponent>()->at(_player);
		auto& v = _ecs.GetComponentArray<VelocityComponent>()->at(_player);

		// For each keykeyStates contains a value of 1 if pressed and a value of 0 if not pressed
		// Add negative and positive velocity so the sprite doesn't move if both are pressed at the same time
		v.Velocity.Y = (-1.0f * keyStates[SDL_SCANCODE_W]) + keyStates[SDL_SCANCODE_S];
		v.Velocity.X = (-1.0f * keyStates[SDL_SCANCODE_A]) + keyStates[SDL_SCANCODE_D];

		// Debug "dash"
		t.Speed = (keyStates[SDL_SCANCODE_RCTRL] ? t.BaseSpeed * 3 : t.BaseSpeed);

		// Update/Play a different Animation, based on the current input
		if (t.Speed > t.BaseSpeed)
			// Dash/Dodge movement
			a.CurrentAnimation = a.GetAnimation("jump");
		else if (v.Velocity.Y != 0.f || v.Velocity.X != 0.f)
			// Normal movement
			a.CurrentAnimation = a.GetAnimation("walk");
		else
			// No movement
			a.CurrentAnimation = a.GetAnimation("idle");
	}
}


void GameState::Update(uint32 frameTime) {
	// Now check for possible collisions
	//_collisionManager.UpdateCollisions(_collidableObjects);

	// Update/Move all objects
	_transformationSystem->Update(frameTime);
	_screenPositionSystem->Update(frameTime);

	// Center the camera over the Player
	auto& t = _ecs.GetComponentArray<TransformationComponent>()->at(_player);
	_camera.x = t.Position.X - (WINDOW_SIZE_WIDTH / 2.f);
	_camera.y = t.Position.Y - (WINDOW_SIZE_HEIGHT / 2.f);

	// Keep the camera in bounds (or not?)
	//if (_camera.x < 0) _camera.x = 0;
	//if (_camera.y < 0) _camera.y = 0;
	//if (_camera.x > _camera.w) _camera.x = _camera.w;
	//if (_camera.y > _camera.h) _camera.y = _camera.h;
}


void GameState::Render() {
	_renderSystem->Render(_camera);

	// First: Render any MapTile batched by Texture hash
	// Second: Render any Entity (NPC, ...) batched by Texture hash
	// Third: Render the Player
	// Last: Render the GUI (always top Layer)
}


void GameState::SetSpawnPosition(Vec2i spawnPoint) {
	// Update the players spawn point
	auto& t = _ecs.GetComponentArray<TransformationComponent>()->at(_player);
	t.Position.X = static_cast<float>(spawnPoint.X);
	t.Position.Y = static_cast<float>(spawnPoint.Y);
}


void GameState::SetEntities(entityId player, const std::vector<entityId>& mapTiles) {
	_player = player;
	_mapTiles = mapTiles;
}
