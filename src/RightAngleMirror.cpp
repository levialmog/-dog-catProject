#include "RightAngleMirror.h"

#include "Resources.h"
#include "Factory.h"

bool RightAngleMirror::m_registerIt = Factory<ControlledObject>::registerIt(R_A_MIRROR, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<ControlledObject> { return std::make_unique<RightAngleMirror>(position, type, world); });

RightAngleMirror::RightAngleMirror(sf::Vector2f position, char type, b2World& world)
	:ControlledObject(Resources::getResources().getSprite(initType(type)),
				  sf::Vector2f(position.x, position.y - CELL_DIMENSIONS.y), STANDARD_RATIO, DOUBLE_RATIO),
	m_isRotated(false)
{
	setBody(world, b2_kinematicBody, false, false);
	
	//add mirror fixture
	addSensor((CELL_DIMENSIONS.x * HALF_RATIO * EIGHTH_RATIO) / PIXEL_METER_RATIO,
			   CELL_DIMENSIONS.y / PIXEL_METER_RATIO, b2Vec2(0, 0), -MIRROR_ANGLE * DEGREE_TO_RADIAN);
}

bool RightAngleMirror::getIsRotated() const
{
	return m_isRotated;
}

void RightAngleMirror::doOperation()
{
	m_isRotated = true;
}

void RightAngleMirror::undoOperation()
{
	m_isRotated = false;
}

void RightAngleMirror::rotateClockwise()
{
	getBody()->SetTransform(getBody()->GetPosition(), ROTATE_ANGLE * DEGREE_TO_RADIAN);
}

void RightAngleMirror::rotateCounterclockwise()
{
	getBody()->SetTransform(getBody()->GetPosition(), 0.f);
}

type RightAngleMirror::initType(char type)
{
	switch (type)
	{
	case PURPLE:
		return type::purpleRightAngleMirror;
		break;

	case GREEN:
		return type::greenRightAngleMirror;
		break;

	default:
		throw std::invalid_argument("Invalid input!");
		break;
	}
}