#include "Button.h"

#include "Resources.h"
#include "Factory.h"

bool Button::m_registerIt = Factory<ControllingObject>::registerIt(BUTTON, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<ControllingObject> { return std::make_unique<Button>(position, type, world); });

Button::Button(sf::Vector2f position, char type, b2World& world)
	:ControllingObject(Resources::getResources().getSprite(initType(type)),
				  sf::Vector2f(position.x, position.y + (CELL_DIMENSIONS.y * QUARTER_RATIO)),
				  HALF_RATIO, HALF_RATIO), m_numOfPushers(0)
{
	setBody(world, b2_staticBody, true, false);
}

void Button::activateControlledObject()
{
	++m_numOfPushers;
	ControllingObject::activateControlledObject();
}

void Button::unactivateControlledObject()
{
	--m_numOfPushers;

	if (m_numOfPushers == 0)
	{
		ControllingObject::unactivateControlledObject();
	}
}
type Button::initType(char type)
{
	switch (type)
	{
	case BLUE:
		return type::blueButton;
		break;

	case RED:
		return type::redButton;
		break;

	default:
		throw std::exception("Invalid input!");
		break;
	}
}