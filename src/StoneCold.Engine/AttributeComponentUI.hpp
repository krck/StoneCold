
#ifndef STONECOLD_COLLISIONCOMPONENT_H
#define STONECOLD_COLLISIONCOMPONENT_H

#include "SDL_Base.hpp"
#include "AnimationComponent.hpp"
#include "Vec2.hpp"

namespace StoneCold::Engine {

//
// UI Element Attribute Component
// Required: ---
// Optional: ---
//
//
//
class AttributeComponentUI : public Component {
public:
	AnimationComponent* _animationComponent;
	UiElementAttribute _uiAttribute;

	AttributeComponentUI(UiElementAttribute defaultAttribute)
		: _animationComponent(nullptr), _uiAttribute(defaultAttribute) { }

	void Init(Entity* entity) override {
		Component::Init(entity);
	}

	bool SetAttribute(UiElementAttribute newAttribute) {
		_uiAttribute = newAttribute;
		switch (_uiAttribute)
		{
		case StoneCold::UiElementAttribute::UIE_Idle:

			break;
		case StoneCold::UiElementAttribute::UIE_Hover:

			break;
		case StoneCold::UiElementAttribute::UIE_Selected:

			break;
		default: break;
		}
	}

	inline UiElementAttribute GetAttribute() const { return _uiAttribute; }

};

}

#endif
