#pragma once

#include "StaticObject.h"

class Floor : public StaticObject
{
public:
	//c-tor:
	Floor(sf::Vector2f, char, b2World&);

	//other functions:
	virtual object getObjectType() override { return object::floorTile; }

private:
	//members:
	static bool m_registerIt;
};