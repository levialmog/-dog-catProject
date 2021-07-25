#pragma once

#include "Command.h"

class HomeCommand : public Command
{
public:
	HomeCommand()
		:Command(type::homeButton,
			sf::Vector2f(SMALL_BUTTON_DIMENSIONS.x / 2, SMALL_BUTTON_DIMENSIONS.y / 2),
			SMALL_BUTTON_DIMENSIONS, std::string()) {}

	virtual bool execute(sf::RenderWindow&) override
	{
		return false;
	}
};