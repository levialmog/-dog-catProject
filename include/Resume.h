#pragma once

#include "Command.h"

class Resume : public Command
{
public:
	Resume()
		:Command(type::resumeButton,
			sf::Vector2f((SMALL_BUTTON_DIMENSIONS.x / 2) + (SMALL_BUTTON_DIMENSIONS.x * 2) + (PAUSE_MENU_BUTTON_PADDING * 5),
						  MAIN_MENU_DIMENSIONS.y + (MAIN_MENU_DIMENSIONS.y / 2)),
			SMALL_BUTTON_DIMENSIONS, std::string()) {}
	virtual bool execute(sf::RenderWindow&) override
	{
		return false;
	}
};