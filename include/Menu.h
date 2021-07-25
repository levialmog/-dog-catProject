#pragma once

#include <memory>
#include "Macros.h"
#include "Command.h"
#include "Resources.h"

class Menu
{
public:
	//c-tor:
	Menu();

	//d-tor:
	~Menu() = default;

	//other functions:
	void add(menu, std::unique_ptr<Command>);
	void activate(sf::RenderWindow&);

private:
	//members:
	typedef std::pair<menu, std::unique_ptr<Command>> option;
	std::vector<option> m_options;
	sf::Sprite m_background;

	//private functions:
	void draw(sf::RenderWindow&);
	int getOptionFromUser(sf::RenderWindow&);
	int click(sf::Vector2f) const;
	bool performAction(int, sf::RenderWindow&);
};