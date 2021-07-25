#pragma once

#include "SFML/Graphics.hpp"
#include "Macros.h"

class MenuButton
{
public:
	//c-tor:
	MenuButton(type, sf::Vector2f, sf::Vector2f, std::string);

	//other functions:
	void draw(sf::RenderWindow&);
	void userClick(sf::RenderWindow&);
	bool isPressed(sf::Vector2f);

private:
	//members:
	sf::Sprite m_sprite;
	sf::Text m_text;

	//private functions:
	void printVictoryParameter(type, float, sf::RenderWindow&);
};