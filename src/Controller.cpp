#include "Controller.h"

#include "Macros.h"
#include "Resources.h"

Controller::Controller()
	:m_background(Resources::getResources().getSprite(type::background)),
	 m_sign(Resources::getResources().getSprite(type::sign)),
     m_text(Resources::getResources().getText()),
     m_isContinue(true), m_isRestart(false)
{
    m_background.setScale(WINDOW_DIMENSIONS.x / (m_background.getLocalBounds().width),
                          WINDOW_DIMENSIONS.y / (m_background.getLocalBounds().height));
    m_sign.setScale((CELL_DIMENSIONS.x * 2.f) / (m_sign.getLocalBounds().width),
                    CELL_DIMENSIONS.y * 1.5f / (m_sign.getLocalBounds().height));
    m_sign.setPosition((WINDOW_DIMENSIONS.x / 2) - CELL_DIMENSIONS.x, 0);
    m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(45);
    m_text.setPosition(WINDOW_DIMENSIONS.x / 2.f, CELL_DIMENSIONS.y / 2.f);

    for (auto level = 0; level < NUM_OF_LEVELS; ++level)
    {
        m_victoryParameters.emplace_back(std::array<bool, 3>{false, false, false});
    }
}

void Controller::setIsRestart(bool status)
{
    m_isRestart = status;
}

void Controller::setIsContinue(bool status)
{
    m_isContinue = status;
}

std::array<bool, 3> Controller::getVictoryParameters(int level)
{
    return m_victoryParameters[level];
}

Controller& Controller::getController()
{
    static Controller controller;
    return controller;
}

bool Controller::run(sf::RenderWindow& window, int levelNumber)
{
    m_board.loadLevel(levelNumber);
    m_timer.restart();

    while (true)
    {
        m_board.worldStep();

        window.clear();
        draw(window);
        window.display();

        if (m_isRestart)
        {
            auto endTime = m_timer.getElapsedTime().asSeconds();
            while (m_timer.getElapsedTime().asSeconds() < endTime + 3.f);
            m_isRestart = false;
            m_board.clearBoard();
            return true;
        }

        if (m_board.areAtHouse())
        {
            auto endTime = m_timer.getElapsedTime().asSeconds();
            while (m_timer.getElapsedTime().asSeconds() < endTime + 3.f);
            victory(endTime, levelNumber);
            return false;
        }

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                m_board.clearBoard();
                window.close();
                exit(EXIT_SUCCESS);
                break;

            case sf::Event::MouseButtonReleased:
                if (event.mouseButton.button == sf::Mouse::Button::Left)
                {
                    if (m_pause.isButtonPressed(window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y })))
                    {
                        Resources::getResources().playSound(gameSounds::click);
                        m_pause.execute(window);
                        if (!m_isContinue)
                        {
                            m_isContinue = true;
                            m_board.clearBoard();
                            return false;
                        }
                        if (m_isRestart)
                        {
                            m_isRestart = false;
                            m_board.clearBoard();
                            return true;
                        }
                    }
                }
                break;
            }
        }
        getKey();
    }
    return false;
}

void Controller::clearBoard()
{
    m_board.clearBoard();
}

void Controller::draw(sf::RenderWindow& window)
{
    window.draw(m_background);
    m_board.draw(window);
    window.draw(m_sign);
    m_text.setString(std::to_string(int(m_timer.getElapsedTime().asSeconds())) + "/" +
                     std::to_string(int(m_board.getLevelTime().asSeconds())));
    m_text.setOrigin(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2);
    window.draw(m_text);
    m_pause.draw(window);
}

void Controller::getKey()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        m_board.movePlayer(UP, type::dog);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
    {
        m_board.movePlayer(RIGHT, type::dog);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
    {
        m_board.movePlayer(LEFT, type::dog);
    }
    else
    {
        m_board.movePlayer(STAND, type::dog);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        m_board.movePlayer(UP, type::cat);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        m_board.movePlayer(RIGHT, type::cat);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        m_board.movePlayer(LEFT, type::cat);
    }
    else
    {
        m_board.movePlayer(STAND, type::cat);
    }
}

void Controller::victory(float endTime, int levelNumber)
{
    Resources::getResources().playSound(gameSounds::win);

    --levelNumber;
    m_victoryParameters[levelNumber][0] = true;

    if (Treat::getNumOfTreats() == 0)
    {
        m_victoryParameters[levelNumber][1] = true;
    }

    if (endTime <= m_board.getLevelTime().asSeconds())
    {
        m_victoryParameters[levelNumber][2] = true;
    }

    m_board.clearBoard();
}
