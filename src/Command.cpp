#include "Command.h"

#include "Resources.h"

Command::Command(type button, sf::Vector2f position, sf::Vector2f size, std::string string)
	:m_menuButton(MenuButton(button, position, size, string))
{
}

void Command::draw(sf::RenderWindow& window)
{
	m_menuButton.draw(window);
}

bool Command::isButtonPressed(sf::Vector2f location)
{
	return m_menuButton.isPressed(location);
}

void Command::buttonUserClick(sf::RenderWindow& window)
{
	m_menuButton.userClick(window);
}
