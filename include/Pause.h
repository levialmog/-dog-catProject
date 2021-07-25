#pragma once

#include "Command.h"
#include "Menu.h"
#include "Levels.h"
#include "Restart.h"
#include "Resume.h"

class Pause : public Command
{
public:
	Pause()
		:Command(type::pauseButton,
			sf::Vector2f(WINDOW_DIMENSIONS.x - SMALL_BUTTON_DIMENSIONS.x / 2, SMALL_BUTTON_DIMENSIONS.y / 2),
			SMALL_BUTTON_DIMENSIONS, std::string()){}

	virtual bool execute(sf::RenderWindow& window) override
	{
		auto pauseMenu = Menu();
		pauseMenu.add(menu::levels, std::make_unique<Levels>());
		pauseMenu.add(menu::restart, std::make_unique<Restart>());
		pauseMenu.add(menu::resume, std::make_unique<Resume>());
		pauseMenu.activate(window);

		return true;
	}
};