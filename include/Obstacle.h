#pragma once

#include "StaticObject.h"

class Obstacle : public StaticObject
{
public:
	//c-tor:
	Obstacle(sf::Vector2f, char, b2World&);

	//access functions:
	type getType() const;

	//other functions:
	virtual object getObjectType() override { return object::obstacle; }

private:
	//members:
	static bool m_registerIt;
	type m_type;

	//private functions:
	type initType(char);
};