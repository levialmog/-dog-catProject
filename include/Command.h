#pragma once

#include "SFML/Graphics.hpp"
#include "MenuButton.h"

class Command
{
public:
	//c-tor:
	Command(type, sf::Vector2f, sf::Vector2f, std::string);

	//d-tor:
	virtual ~Command() = default;

	//other functions:
	virtual bool execute(sf::RenderWindow&) = 0;
	void draw(sf::RenderWindow&);
	bool isButtonPressed(sf::Vector2f);
	void buttonUserClick(sf::RenderWindow&);

private:
	//members:
	MenuButton m_menuButton;
};