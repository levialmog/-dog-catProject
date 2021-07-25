#pragma once

#include "ControlledObject.h"

class RightAngleMirror : public ControlledObject
{
public:
	//c-tor:
	RightAngleMirror(sf::Vector2f, char, b2World&);

	//access functions:
	bool getIsRotated() const;

	//other functions:
	virtual object getObjectType() override { return object::rightAngleMirror; }
	virtual void doOperation() override;
	virtual void undoOperation() override;
	void rotateClockwise();
	void rotateCounterclockwise();

private:
	//members:
	bool m_isRotated;
	static bool m_registerIt;

	//private functions:
	type initType(char);
};