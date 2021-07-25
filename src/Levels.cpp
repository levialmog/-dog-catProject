#include "Levels.h"
#include "Controller.h"

Levels::Levels()
	:Command(type::levelsButton,
			 sf::Vector2f(SMALL_BUTTON_DIMENSIONS.x / 2 + (PAUSE_MENU_BUTTON_PADDING * 3),
						  MAIN_MENU_DIMENSIONS.y + (MAIN_MENU_DIMENSIONS.y / 2)),
		SMALL_BUTTON_DIMENSIONS, std::string())
{
}

bool Levels::execute(sf::RenderWindow&)
{
	Controller::getController().setIsContinue(false);
	return false;
}