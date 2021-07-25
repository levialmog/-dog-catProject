#pragma once

#include "StaticObject.h"

class ControlledObject : public StaticObject
{
public:
	//c-tor:
	ControlledObject(sf::Sprite, sf::Vector2f, float = 1, float = 1);

	//other functions:
	virtual void doOperation() = 0;
	virtual void undoOperation() = 0;
};