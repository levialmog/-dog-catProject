#include "LaserDestination.h"

#include "Resources.h"
#include "Factory.h"

bool LaserDestination::m_registerIt = Factory<ControllingObject>::registerIt(LASER_DESTINATION, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<ControllingObject> { return std::make_unique<LaserDestination>(position, type, world); });

LaserDestination::LaserDestination(sf::Vector2f sourcePosition, char, b2World& world)
	:ControllingObject(Resources::getResources().getSprite(type::laserDestination),
		sf::Vector2f(sourcePosition.x - (CELL_DIMENSIONS.x * HALF_RATIO), sourcePosition.y),
		QUARTER_RATIO, STANDARD_RATIO)
{
	setBody(world, b2_staticBody, false, false);
}