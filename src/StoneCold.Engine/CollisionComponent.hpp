
#ifndef STONECOLD_COLLISIONCOMPONENT_H
#define STONECOLD_COLLISIONCOMPONENT_H

#include "SDL_Base.hpp"
#include "Component.hpp"
#include "Vec2.hpp"
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
	const Vec2 Hitbox;
	SDL_FRect CollisionBox;
	CollisionComponent* CollisionWith;

	CollisionComponent(const std::string& tag, bool isFixed, Vec2 hitbox, SDL_FRect collisionBox)
		: Tag(tag), IsFixed(isFixed), Hitbox(hitbox), CollisionBox(collisionBox), CollisionWith(nullptr) { }

	void Init(GameObject* gameObject) override {
		IComponent::Init(gameObject);
	}

	inline bool HasHitbox() const { return (Hitbox.X > 0.f && Hitbox.Y > 0.f) && (Hitbox.X < CollisionBox.w && Hitbox.Y < CollisionBox.h); }
	inline bool HasCollision() const { return (CollisionWith != nullptr); }
};

}

#endif
