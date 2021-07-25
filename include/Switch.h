#pragma once

#include "ControllingObject.h"

class Switch : public ControllingObject
{
public:
	//c-tor:
	Switch(sf::Vector2f, char, b2World&);

	//other functions:
	virtual object getObjectType() override { return object::switchObject; }
	virtual void activateControlledObject() override;
	virtual void unactivateControlledObject() override;

private:
	//members:
	bool m_isOn;
	static bool m_registerIt;

	//private functions:
	type initType(char);
};