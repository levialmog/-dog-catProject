#include "Restart.h"
#include "Controller.h"

Restart::Restart()
	:Command(type::restartButton,
			 sf::Vector2f((SMALL_BUTTON_DIMENSIONS.x / 2) + SMALL_BUTTON_DIMENSIONS.x + (PAUSE_MENU_BUTTON_PADDING * 4),
						   MAIN_MENU_DIMENSIONS.y + (MAIN_MENU_DIMENSIONS.y / 2)),
		SMALL_BUTTON_DIMENSIONS, std::string())
{
}

bool Restart::execute(sf::RenderWindow&)
{
	Controller::getController().setIsRestart(true);
	return false;
}
