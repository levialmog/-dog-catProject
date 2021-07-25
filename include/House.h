#pragma once

#include "StaticObject.h"

class House : public StaticObject
{
public:
	//c-tor:
	House(sf::Vector2f, char, b2World&);

	//access functions:
	type getType() const;

	//other functions:
	virtual object getObjectType() override { return object::house; }

private:
	//members:
	type m_type;
	static bool m_registerIt;

	//private functions:
	type initType(char);
};