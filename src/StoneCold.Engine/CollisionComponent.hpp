
#ifndef STONECOLD_COLLISIONCOMPONENT_H
#define STONECOLD_COLLISIONCOMPONENT_H

#include "SDL_Base.hpp"
#include "Component.hpp"
#include <string>

namespace StoneCold::Engine {

//
// 2D Collision Component 
// Dependent on: ---
//
// Has no direct dendencies, but the _collisionDimensions must be
// updated by either a TransformComponent or the SpriteComponentFixed
//
class CollisionComponent : public IComponent {
public:
	const std::string Tag;
	const bool IsFixed;
	std::string CollisionWithTag;
	SDL_FRect CollisionDimensions;

	CollisionComponent(const std::string& tag, bool isFixed, SDL_FRect collisionDimensions)
		: Tag(tag), IsFixed(isFixed), CollisionDimensions(collisionDimensions) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
	}

	inline bool HasCollision() const { return !CollisionWithTag.empty(); }
};

}

#endif
