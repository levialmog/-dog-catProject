#include "Switch.h"

#include "Resources.h"
#include "Factory.h"

bool Switch::m_registerIt = Factory<ControllingObject>::registerIt(SWITCH, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<ControllingObject> { return std::make_unique<Switch>(position, type, world); });

Switch::Switch(sf::Vector2f position, char type, b2World& world)
	:ControllingObject(Resources::getResources().getSprite(initType(type)), position, HALF_RATIO, STANDARD_RATIO),
	m_isOn(false)
{
	setBody(world, b2_staticBody, true, false);
}

void Switch::activateControlledObject()
{
	if(!m_isOn)
	{
		m_isOn = true;
		ControllingObject::activateControlledObject();
		flipSprite();
	}
}

void Switch::unactivateControlledObject()
{
	if (m_isOn)
	{
		m_isOn = false;
		ControllingObject::unactivateControlledObject();
		flipSprite();
	}
}

type Switch::initType(char type)
{
	switch (type)
	{
	case GREEN:
		return type::greenSwitch;
		break;

	case PURPLE:
		return type::purpleSwitch;
		break;

	default:
		throw std::exception("Invalid input!");
		break;
	}
}
