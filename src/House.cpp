#include "House.h"

#include "Resources.h"
#include "Factory.h"

bool House::m_registerIt = Factory<StaticObject>::registerIt(HOUSE, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<StaticObject> { return std::make_unique<House>(position, type, world); });

House::House(sf::Vector2f position, char type, b2World& world)
	:StaticObject(Resources::getResources().getSprite(initType(type)),
				  sf::Vector2f(position.x, position.y - (CELL_DIMENSIONS.y * HALF_RATIO)), STANDARD_RATIO, DOUBLE_RATIO)
{
	setBody(world, b2_staticBody, true, false);
}

type House::getType() const
{
	return m_type;
}

type House::initType(char type)
{
	switch (type)
	{
	case OF_DOG:
		m_type = type::dog;
		return type::dogHouse;
		break;

	case OF_CAT:
		m_type = type::cat;
		return type::catHouse;
		break;

	default:
		throw std::invalid_argument("Invalid input!");
		break;
	}
}