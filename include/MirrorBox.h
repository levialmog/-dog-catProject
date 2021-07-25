#pragma once

#include "MoveableObject.h"
#include "Button.h"

class MirrorBox : public MoveableObject
{
public:
	//c-tor:
	MirrorBox(sf::Vector2f, char, b2World&);

	//other functions:
	virtual object getObjectType() override { return object::mirrorBox; }
	void startContact(Button*);
	void endContact(Button*);

private:
	//members:
	static bool m_registerIt;
};