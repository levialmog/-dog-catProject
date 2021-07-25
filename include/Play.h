#pragma once

#include "Command.h"
#include "Menu.h"
#include "StartLevel.h"
#include "HomeCommand.h"

class Play : public Command
{
public:
	Play()
		:Command(type::playButton,
				 sf::Vector2f(float(WINDOW_DIMENSIONS.x / 2), MAIN_MENU_DIMENSIONS.y + (MAIN_MENU_BUTTON_DIMENSIONS.y / 2)),
				 MAIN_MENU_BUTTON_DIMENSIONS, std::string()){}

	virtual bool execute(sf::RenderWindow& window) override
	{
		auto levelMenu = Menu();

		for (auto level = 1; level <= NUM_OF_LEVELS; ++level)
		{
			levelMenu.add(menu::startLevel, std::make_unique<StartLevel>(level));
		}

		levelMenu.add(menu::homeMenu, std::make_unique<HomeCommand>());

		levelMenu.activate(window);

		return true;
	}
};