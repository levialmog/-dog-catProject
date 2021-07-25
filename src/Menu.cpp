#include "Menu.h"

#include "SFML/Graphics.hpp"
#include "Controller.h"

Menu::Menu()
    :m_background(Resources::getResources().getSprite(type::menuBackground))
{
    m_background.setScale(WINDOW_DIMENSIONS.x / (m_background.getLocalBounds().width),
                          WINDOW_DIMENSIONS.y / (m_background.getLocalBounds().height));
}

void Menu::add(menu name, std::unique_ptr<Command> command)
{
	m_options.emplace_back(option(name, move(command)));
}

void Menu::activate(sf::RenderWindow& window)
{
	int command;
	do {
		draw(window);
		command = getOptionFromUser(window);
	} while(performAction(command, window));
}

void Menu::draw(sf::RenderWindow& window)
{
    window.clear();
    window.draw(m_background);
    for (const auto& option : m_options)
    {
        option.second->draw(window);
    }
    window.display();
}

int Menu::getOptionFromUser(sf::RenderWindow& window)
{
    for (auto event = sf::Event{}; window.waitEvent(event);)
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            Controller::getController().clearBoard();
            window.close();
            exit(EXIT_SUCCESS);
            break;

        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                auto command = click(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }));
                if (command != -1)
                {
                    return command;
                }
            }
            break;
        }
    }
    return false;
}

int Menu::click(sf::Vector2f location) const
{
    for (int button = 0; button < m_options.size(); ++button)
    {
        if (m_options[button].second->isButtonPressed(location))
        {
            Resources::getResources().playSound(gameSounds::click);
            return button;
        }
    }
    return -1;
}

bool Menu::performAction(int command, sf::RenderWindow& window)
{
	return m_options[command].second->execute(window);
}
