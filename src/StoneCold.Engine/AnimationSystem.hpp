
#ifndef STONECOLD_ANIMATIONSYSTEM_H
#define STONECOLD_ANIMATIONSYSTEM_H

#include "System.hpp"
#include "Components.hpp"
#include "EntityComponentArray.hpp"

namespace StoneCold::Engine {

class AnimationSystem : public System {
public:
	//
	// Hardcoded System Component-Mask: 
	// Only Entities with a Animation and Screen-Position Component will be updated with this System
	//
	AnimationSystem(EntityComponentArray<AnimationComponent>& animation, EntityComponentArray<ScreenPositionComponent>& position)
		: System((GetComponentMask<AnimationComponent>() | GetComponentMask<ScreenPositionComponent>()))
		, _timeElapsed(0), _animationComponents(animation), _positionComponents(position) { }

	AnimationSystem(const AnimationSystem&) = delete;
	AnimationSystem& operator=(const AnimationSystem&) = delete;

	virtual void Update(uint32 frameTime) override {
		_timeElapsed += frameTime;
		for (const auto& entityId : _entities) {
			auto& a = _animationComponents[entityId];
			auto& p = _positionComponents[entityId];

			// Udpate the Animation index based on its "play-speed" in case its set to automaticUpdate
			// FIND SOME WAY TO DO THIS WITHOUT IFs TO NOT DISTURB THE CACHE, OUR LORD AND SAVIOR
			if (_timeElapsed > a.CurrentAnimation->FrameTime) {
				_timeElapsed -= a.CurrentAnimation->FrameTime;
				a.CurrentFrameIndex = (a.CurrentFrameIndex < a.CurrentAnimation->FrameCount ? a.CurrentFrameIndex + 1 : 0);
			}

			p.SrcRect = a.CurrentAnimation->FramePositions[a.CurrentFrameIndex];
		}
	}

private:
	uint32 _timeElapsed;
	EntityComponentArray<AnimationComponent>& _animationComponents;
	EntityComponentArray<ScreenPositionComponent>& _positionComponents;
};

}

#endif
