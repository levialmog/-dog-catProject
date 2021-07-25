#pragma once

#include "Command.h"
#include "Controller.h"

class StartLevel : public Command
{
public:
	StartLevel(int levelNumber)
		:Command(type::menuButton,
				 sf::Vector2f((SMALL_BUTTON_DIMENSIONS.x * (levelNumber - 1)) + (SMALL_BUTTON_DIMENSIONS.x / 2) +
							  (LEVELS_BUTTON_PADDING * levelNumber),
							  LEVEL_MENU_DIMENSIONS.y + (LEVEL_MENU_DIMENSIONS.y / 2)),
				 SMALL_BUTTON_DIMENSIONS, std::string(std::to_string(levelNumber))),
				 m_levelNumber(levelNumber){}

	virtual bool execute(sf::RenderWindow& window) override
	{
		if (m_levelNumber == 1 ||
		   (Controller::getController().getVictoryParameters(m_levelNumber - 2)[0] && m_levelNumber != 1))
		{
			while (Controller::getController().run(window, m_levelNumber));
		}
			return true;
	}

private:
	int m_levelNumber;
};