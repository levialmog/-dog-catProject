#pragma once

#include "ControllingObject.h"

class Button : public ControllingObject
{
public:
	//c-tor:
	Button(sf::Vector2f, char, b2World&);

	//other functions:
	virtual object getObjectType() override { return object::button; }
	virtual void activateControlledObject() override;
	virtual void unactivateControlledObject() override;

private:
	//members:
	int m_numOfPushers;
	static bool m_registerIt;

	//private functions:
	type initType(char);
};