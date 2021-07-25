#pragma once

#include "ControllingObject.h"

class LaserDestination : public ControllingObject
{
public:
	//c-tor:
	LaserDestination(sf::Vector2f, char, b2World&);

	//other functions:
	virtual object getObjectType() override { return object::laserDestination; }

private:
	//members:
	static bool m_registerIt;
};