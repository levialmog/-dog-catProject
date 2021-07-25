#pragma once

#include "Command.h"


class Levels : public Command
{
public:
	//c-tor:
	Levels();
	
	//other functions:
	virtual bool execute(sf::RenderWindow& window) override;
};