#include "Floor.h"

#include "Resources.h"
#include "Factory.h"

bool Floor::m_registerIt = Factory<StaticObject>::registerIt(FLOOR, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<StaticObject> { return std::make_unique<Floor>(position, type, world); });

Floor::Floor(sf::Vector2f position, char, b2World& world)
	:StaticObject(Resources::getResources().getSprite(type::floorTile), position)
{
	setBody(world, b2_staticBody, false, false);
}