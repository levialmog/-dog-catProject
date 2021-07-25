#pragma once

#include "StaticObject.h"
#include "ControlledObject.h"

class ControllingObject : public StaticObject
{
public:
	//c-tor:
	ControllingObject(sf::Sprite, sf::Vector2f, float = 1, float = 1);

	//access functions:
	void setControlledPtr(ControlledObject*);

	//other functions:
	virtual void activateControlledObject();
	virtual void unactivateControlledObject();
	
private:
	//members:
	ControlledObject* m_controlled;
};