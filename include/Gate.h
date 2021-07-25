#pragma once

#include "ControlledObject.h"

class Gate : public ControlledObject
{
public:
	//c-tor:
	Gate(sf::Vector2f, char, b2World&);

	//other functions:
	virtual object getObjectType() override { return object::gate; }
	virtual void doOperation() override;
	virtual void undoOperation() override;

private:
	//members:
	static bool m_registerIt;

	//private functions:
	type initType(char);
};