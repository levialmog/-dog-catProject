#include "MenuButton.h"

#include "Resources.h"
#include "Macros.h"
#include "Controller.h"

MenuButton::MenuButton(type button, sf::Vector2f position, sf::Vector2f size, std::string string)
	:m_sprite(Resources::getResources().getSprite(button)), m_text(Resources::getResources().getText())
{
	m_sprite.setScale(size.x / (m_sprite.getLocalBounds().width),
                      size.y / (m_sprite.getLocalBounds().height));
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(position);

	m_text.setString(string);
    m_text.setCharacterSize(100);
    m_text.setFillColor(sf::Color::White);
	m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
	m_text.setPosition(position.x, position.y - 50);
}

void MenuButton::draw(sf::RenderWindow& window)
{
    if (m_text.getString() != std::string())
    {
        std::string level = m_text.getString();
        auto levelNumber = std::stoi(level);

        if (levelNumber == 1 ||
            (Controller::getController().getVictoryParameters(levelNumber - 2)[0] && levelNumber != 1))
        {
            m_sprite.setColor(sf::Color(255, 255, 255, 255));
            std::array<bool, 3> victoryParameters = Controller::getController().getVictoryParameters(levelNumber - 1);
            if (victoryParameters[0])
            {
                printVictoryParameter(type::dogCatIcon, -VICTORY_PARAMETER_DIMENSIONS.x, window);
            }
            if (victoryParameters[1])
            {
                printVictoryParameter(type::treats, 0, window);
            }
            if (victoryParameters[2])
            {
                printVictoryParameter(type::clockIcon, VICTORY_PARAMETER_DIMENSIONS.x, window);
            }
        }
        else
        {
            m_sprite.setColor(sf::Color(255, 255, 255, 100));
        }
    }

    window.draw(m_sprite);
    window.draw(m_text);
}

void MenuButton::userClick(sf::RenderWindow& window)
{
    for (auto event = sf::Event{}; window.waitEvent(event);)
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            exit(EXIT_SUCCESS);
            break;

        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Button::Left)
            {
                if (isPressed(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
                {
                    Resources::getResources().playSound(gameSounds::click);
                    return;
                }
            }
            break;
        }
    }
}

bool MenuButton::isPressed(sf::Vector2f location)
{
	return m_sprite.getGlobalBounds().contains(location);
}

void MenuButton::printVictoryParameter(type type, float diff, sf::RenderWindow& window)
{
    auto icon = Resources::getResources().getSprite(type);

    icon.setScale(VICTORY_PARAMETER_DIMENSIONS.x / (icon.getLocalBounds().width),
                  VICTORY_PARAMETER_DIMENSIONS.y / (icon.getLocalBounds().height));
    icon.setOrigin(icon.getLocalBounds().width / 2, icon.getLocalBounds().height / 2);
    icon.setPosition(m_sprite.getPosition().x + diff, m_sprite.getPosition().y + SMALL_BUTTON_DIMENSIONS.y);
    window.draw(icon);
}
