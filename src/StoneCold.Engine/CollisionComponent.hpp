
#ifndef STONECOLD_COLLISIONCOMPONENT_H
#define STONECOLD_COLLISIONCOMPONENT_H

#include "SDL_Base.hpp"
#include "Component.hpp"
#include <string>

namespace StoneCold::Engine {

//
// 2D Collision Component 
// Required: ---
// Optional: ---
//
// Has no direct dendencies, but the Hitbox can be updated by a TransformComponent
// and the CollisionWith-Pointer will be set by the CollisionManager in case of overlap
//
class CollisionComponent : public IComponent {
public:
	const std::string Tag;
	const bool IsFixed;
	SDL_FRect Hitbox;
	CollisionComponent* CollisionWith;

	CollisionComponent(const std::string& tag, bool isFixed, SDL_FRect hitbox)
		: Tag(tag), IsFixed(isFixed), Hitbox(hitbox), CollisionWith(nullptr) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
	}

	inline bool HasCollision() const { return (CollisionWith != nullptr); }
};

}

#endif
