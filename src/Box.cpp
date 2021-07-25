#include "Box.h"

#include "Resources.h"
#include "Factory.h"

bool Box::m_registerIt = Factory<MoveableObject>::registerIt(BOX, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<MoveableObject> { return std::make_unique<Box>(position, type, world); });

Box::Box(sf::Vector2f position, char, b2World& world)
	:MoveableObject(Resources::getResources().getSprite(type::box), position, HALF_RATIO, STANDARD_RATIO)
{
	setBody(world, b2_dynamicBody, false, false);
}

void Box::startContact(Button* button)
{
	button->activateControlledObject();
}

void Box::endContact(Button* button)
{
	button->unactivateControlledObject();
}
