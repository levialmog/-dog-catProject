#include "MirrorBox.h"

#include "Resources.h"
#include "Factory.h"

bool MirrorBox::m_registerIt = Factory<MoveableObject>::registerIt(MIRROR_BOX, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<MoveableObject> { return std::make_unique<MirrorBox>(position, type, world); });

MirrorBox::MirrorBox(sf::Vector2f position, char, b2World& world)
	:MoveableObject(Resources::getResources().getSprite(type::mirrorBox), position, HALF_RATIO, STANDARD_RATIO)
{
	setBody(world, b2_dynamicBody, false, false);

	//add mirror fixture
	addSensor((CELL_DIMENSIONS.x * HALF_RATIO * EIGHTH_RATIO) / PIXEL_METER_RATIO,
			  ((CELL_DIMENSIONS.y * HALF_RATIO) / PIXEL_METER_RATIO), b2Vec2(0, 0), MIRROR_ANGLE * DEGREE_TO_RADIAN);
}

void MirrorBox::startContact(Button* button)
{
	button->activateControlledObject();
}

void MirrorBox::endContact(Button* button)
{
	button->unactivateControlledObject();
}