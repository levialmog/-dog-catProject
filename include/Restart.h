#pragma once

#include "Command.h"

class Restart : public Command
{
public:
	//c-tor:
	Restart();
		
	//other functions:
	virtual bool execute(sf::RenderWindow& window) override;
};