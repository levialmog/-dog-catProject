#pragma once

#include "StaticObject.h"

class Treat : public StaticObject
{
public:
	//c-tor:
	Treat(sf::Vector2f, char, b2World&);
	
	//d-tor:
	~Treat();

	//access functions:
	type getType() const;
	bool getIsTaken() const;
	void setIsTaken(bool);
	static int getNumOfTreats();

	//other functions:
	virtual object getObjectType() override { return object::treat; }

private:
	//members:
	static int m_numOfTreats;
	type m_type;
	bool m_isTaken;
	static bool m_registerIt;

	//private functions:
	type initType(char);
};