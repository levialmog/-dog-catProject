#pragma once

#include "Command.h"

class Exit : public Command
{
public:
	Exit()
		:Command(type::exitButton,
			sf::Vector2f(float(WINDOW_DIMENSIONS.x / 2), MAIN_MENU_DIMENSIONS.y + (MAIN_MENU_BUTTON_DIMENSIONS.y / 2) + (MAIN_MENU_BUTTON_DIMENSIONS.y * 2)),
			MAIN_MENU_BUTTON_DIMENSIONS, std::string()) {}
	virtual bool execute(sf::RenderWindow&) override
	{
		return false;
	}
};