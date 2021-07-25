#include "Obstacle.h"

#include "Resources.h"
#include "Factory.h"

bool Obstacle::m_registerIt = Factory<StaticObject>::registerIt(OBSTACLE, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<StaticObject> { return std::make_unique<Obstacle>(position, type, world); });

Obstacle::Obstacle(sf::Vector2f position, char type, b2World& world)
	:StaticObject(Resources::getResources().getSprite(initType(type)), position)
{
	setBody(world, b2_staticBody, false, false);
}

type Obstacle::getType() const
{
	return m_type;
}

type Obstacle::initType(char type)
{
	switch (type)
	{
	case OF_DOG:
		m_type = type::dog;
		return type::orangeObstacle;
		break;

	case OF_CAT:
		m_type = type::cat;
		return type::grayObstacle;
		break;

	case OF_EVERYONE:
		m_type = type::blueObstacle;
		return type::blueObstacle;
		break;

	default:
		throw std::invalid_argument("Invalid input!");
		break;
	}
}
