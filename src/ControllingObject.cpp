#include "ControllingObject.h"

ControllingObject::ControllingObject(sf::Sprite sprite, sf::Vector2f position, float widthRatio, float heightRatio)
	:StaticObject(sprite, position, widthRatio, heightRatio), m_controlled(nullptr)
{
}

void ControllingObject::setControlledPtr(ControlledObject* controlledPtr)
{
	m_controlled = controlledPtr;
}

void ControllingObject::activateControlledObject()
{
	m_controlled->doOperation();
}

void ControllingObject::unactivateControlledObject()
{
	m_controlled->undoOperation();
}
