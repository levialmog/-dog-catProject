#include "Gate.h"

#include "Resources.h"
#include "Factory.h"

bool Gate::m_registerIt = Factory<ControlledObject>::registerIt(GATE, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<ControlledObject> { return std::make_unique<Gate>(position, type, world); });

Gate::Gate(sf::Vector2f position, char type, b2World& world)
	:ControlledObject(Resources::getResources().getSprite(initType(type)), position, STANDARD_RATIO, HALF_RATIO)
{
	setBody(world, b2_staticBody, false, false);
}

void Gate::doOperation()
{
	auto filter = getBody()->GetFixtureList()->GetFilterData();
	filter.groupIndex = -1;
	getBody()->GetFixtureList()->SetSensor(true);
	getBody()->GetFixtureList()->SetFilterData(filter);
	setIsAppear(false);
}

void Gate::undoOperation()
{
	auto filter = getBody()->GetFixtureList()->GetFilterData();
	filter.groupIndex = 0;
	getBody()->GetFixtureList()->SetSensor(false);
	getBody()->GetFixtureList()->SetFilterData(filter);
	setIsAppear(true);
}

type Gate::initType(char type)
{
	switch (type)
	{
	case BLUE:
		return type::blueGate;
		break;

	case RED:
		return type::redGate;
		break;

	case PURPLE:
		return type::purpleGate;
		break;

	case GREEN:
		return type::greenGate;
		break;

	case YELLOW:
		return type::yellowGate;
		break;

	default:
		throw std::exception("Invalid input!");
		break;
	}
}