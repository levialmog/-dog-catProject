#pragma once

#include "Command.h"
#include "Menu.h"
#include "HomeCommand.h"

class Help : public Command
{
public:
	Help()
		:Command(type::helpButton,
			sf::Vector2f(float(WINDOW_DIMENSIONS.x / 2), MAIN_MENU_DIMENSIONS.y + (MAIN_MENU_BUTTON_DIMENSIONS.y / 2) + MAIN_MENU_BUTTON_DIMENSIONS.y),
			MAIN_MENU_BUTTON_DIMENSIONS, std::string()) {}
	virtual bool execute(sf::RenderWindow& window) override
	{
		//help window
		auto homeCommand = HomeCommand();
		window.clear();
		auto instructions = Resources::getResources().getSprite(type::instructions);
		instructions.setScale(WINDOW_DIMENSIONS.x / (instructions.getLocalBounds().width),
							  WINDOW_DIMENSIONS.y / (instructions.getLocalBounds().height));
		window.draw(instructions);
		homeCommand.draw(window);
		window.display();
		homeCommand.buttonUserClick(window);

		return true;
	}
};