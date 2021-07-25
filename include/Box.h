#pragma once

#include "MoveableObject.h"
#include "button.h"

class Box : public MoveableObject
{
public:
	//c-tor:
	Box(sf::Vector2f, char, b2World&);

	//other functions:
	virtual object getObjectType() override { return object::box; }
	void startContact(Button*);
	void endContact(Button*);

private:
	//members:
	static bool m_registerIt;
};