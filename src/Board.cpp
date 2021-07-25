#include "Board.h"

#include <fstream>
#include "Macros.h"
#include "ContactListener.h"
#include "Factory.h"
#include "RightAngleMirror.h"
#include "LaserDestination.h"
#include "Resources.h"

ContactListener contactListenerInstance;

Board::Board()
    : m_levelTime(sf::seconds(0)), m_laserSource(nullptr), m_world(nullptr)
{
}

Board::~Board()
{
    if (m_world)
    {
        delete m_world;
        m_world = nullptr;
    }
}

sf::Time Board::getLevelTime() const
{
    return m_levelTime;
}

void Board::loadLevel(int level)
{
    m_world = new b2World(b2Vec2(0.0f, 9.8f));
    m_world->SetContactListener(&contactListenerInstance);

    std::ifstream boardFile;

    std::string fileName = std::to_string(level) + ".txt";

    boardFile.open(fileName);

    if (!boardFile.is_open())
    {
        throw std::runtime_error("Cannot open level file!");
    }

    float levelTime = 0;
    boardFile >> levelTime;

    if (!levelTime)
    {
        throw std::invalid_argument("Invalid input!");
    }

    boardFile.get();
    m_levelTime = sf::seconds(levelTime);

    auto s = std::string();
    char character,
        type = 'E';
    int row, col;
    ControlledObject* p2controlled = nullptr;

    for (row = 0; row < BOARD_DIMENSIONS.y; ++row)
    {
        for (col = 0; col < BOARD_DIMENSIONS.x; ++col)
        {
            character = boardFile.get();
            createObject(character, row, col, type, p2controlled);
        }
        boardFile.get();
    }

    while (std::getline(boardFile, s))
    {
        auto iss = std::istringstream(s);
        type = 'E';

        iss >> character >> row >> col;

        if (row > (BOARD_DIMENSIONS.y - 1) || row < 0 || col >(BOARD_DIMENSIONS.x - 1) || col < 0)
        {
            throw std::invalid_argument("Invalid input!");
        }

        if (!(iss.eof() || (iss >> std::ws).eof()))
        {
            iss >> type;
        }

        createObject(character, row, col, type, p2controlled);
    }
}

void Board::createObject(char character, int row, int col, char type, ControlledObject*& p2controlled)
{
    auto object1 = Factory<ControllingObject>::create(character, calPosition(row, col), type, *m_world);
    if (object1)
    {
        object1->setControlledPtr(p2controlled);
        m_staticObjects.emplace_back(std::unique_ptr<ControllingObject>());
        m_staticObjects[m_staticObjects.size() - 1] = std::move(object1);
        return;
    }

    auto object2 = Factory<ControlledObject>::create(character, calPosition(row, col), type, *m_world);
    if (object2)
    {
        p2controlled = object2.get();
        m_staticObjects.emplace_back(std::unique_ptr<ControlledObject>());
        m_staticObjects[m_staticObjects.size() - 1] = std::move(object2);
        return;
    }

    auto object3 = Factory<LaserSource>::create(character, calPosition(row, col), type, *m_world);
    if (object3)
    {
        m_laserSource = std::move(object3);
        return;
    }

    auto object4 = Factory<StaticObject>::create(character, calPosition(row, col), type, *m_world);
    if (object4)
    {
        m_staticObjects.emplace_back(std::unique_ptr<StaticObject>());
        m_staticObjects[m_staticObjects.size() - 1] = std::move(object4);
        return;
    }

    auto object5 = Factory<Player>::create(character, calPosition(row, col), type, *m_world);
    if (object5)
    {
        if (type == OF_DOG)
        {
            m_dog = std::move(object5);
        }
        else
        {
            m_cat = std::move(object5);
        }
        return;
    }

    auto object6 = Factory<MoveableObject>::create(character, calPosition(row, col), type, *m_world);
    if (object6)
    {
        m_moveableObjects.emplace_back(std::unique_ptr<MoveableObject>());
        m_moveableObjects[m_moveableObjects.size() - 1] = std::move(object6);
        return;
    }

    if (character != EMPTY)
    {
        throw std::invalid_argument("Invalid input!");
    }
}

void Board::draw(sf::RenderWindow& window)
{
    for (const auto& object : m_staticObjects)
    {
        if (object->getIsAppear())
        {
            object->draw(window);
        }
    }

    if (m_laserSource)
    {
        m_laserSource->draw(window);
    }

    for (const auto& object : m_moveableObjects)
    {
        object->draw(window);
    }

    m_dog->draw(window);
    m_cat->draw(window);
}

void Board::worldStep()
{
    m_world->Step(1.0f / 60.0f, 9, 3);

    for (auto object = 0; object < m_staticObjects.size(); ++object)
    {
        if (m_staticObjects[object])
        {
            if (m_staticObjects[object]->getObjectType() == object::treat)
            {
                auto treat = static_cast<Treat*>(m_staticObjects[object].get());
                if (treat->getIsTaken())
                {
                    m_staticObjects.erase(m_staticObjects.begin() + object);
                }
            }

            if (m_staticObjects[object]->getObjectType() == object::rightAngleMirror)
            {
                auto rightAngleMirror = static_cast<RightAngleMirror*>(m_staticObjects[object].get());
                if (rightAngleMirror->getIsRotated())
                {
                    rightAngleMirror->rotateClockwise();
                }
                else
                {
                    rightAngleMirror->rotateCounterclockwise();
                }
            }

            if (m_staticObjects[object]->getObjectType() == object::house)
            {
                auto house = static_cast<House*>(m_staticObjects[object].get());
                if (house->getType() == type::dog)
                {
                    checkIsAtHouse(house, m_dog.get());
                }
                else
                {
                    checkIsAtHouse(house, m_cat.get());
                }
            }

            if (m_staticObjects[object]->getObjectType() == object::laserDestination)
            {
                auto laserDestination = static_cast<LaserDestination*>(m_staticObjects[object].get());
                laserDestination->unactivateControlledObject();
            }
        }
    }

    if (m_laserSource)
    {
        m_laserSource->laser(*m_world);
    }
}

void Board::movePlayer(b2Vec2 direction, type type)
{
    switch (type)
    {
    case type::dog:
        m_dog->move(direction);
        break;

    case type::cat:
        m_cat->move(direction);
        break;

    default:
        break;
    }
}

bool Board::areAtHouse() const
{
    return m_dog->getIsAtHouse() && m_cat->getIsAtHouse() ? true : false;
}

status Board::getPlayerLastStatus(type type) const
{
    if (type == type::dog)
    {
        return m_dog->getLastStatus();
    }
    else
    {
        return m_cat->getLastStatus();
    }
}

void Board::clearBoard()
{
    m_staticObjects.clear();
    m_moveableObjects.clear();
    m_laserSource = nullptr;
    m_dog = nullptr;
    m_cat = nullptr;
    delete m_world;
    m_world = nullptr;
}

sf::Vector2f Board::calPosition(int row, int col)
{
    sf::Vector2f position;

    position.y = float(CELL_DIMENSIONS.y * (row)+(CELL_DIMENSIONS.y / 2));
    position.x = float(CELL_DIMENSIONS.x * (col)+(CELL_DIMENSIONS.x / 2));

    return position;
}

void Board::checkIsAtHouse(House* house, Player* player)
{
    if (house->getSpriteGlobalBounds().contains(player->getSpriteGlobalBounds().left, player->getSpriteGlobalBounds().top + DIFF) &&
        house->getSpriteGlobalBounds().contains(player->getSpriteGlobalBounds().left + player->getSpriteGlobalBounds().width,
            player->getSpriteGlobalBounds().top + player->getSpriteGlobalBounds().height - DIFF))
    {
        if (!player->getIsAtHouse())
        {
            player->setIsAtHouse(true);
            Resources::getResources().playSound(gameSounds::doorbell);
        }
    }
    else
    {
        player->setIsAtHouse(false);
    }
}
