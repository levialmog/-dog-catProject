#pragma once

#include <vector> 
#include <SFML/Graphics.hpp>
#include <Box2D/box2D.h>
#include <sstream>
#include "StaticObject.h"
#include "MoveableObject.h"
#include "Player.h"
#include "LaserSource.h"

class Board
{
public:
	//c-tor:
	Board();

	//d-tor:
	~Board();

	//access functions:
	sf::Time getLevelTime() const;

	//other functions:
	void loadLevel(int);
	void draw(sf::RenderWindow&);
	void worldStep();
	void movePlayer(b2Vec2, type);
	bool areAtHouse() const;
	status getPlayerLastStatus(type) const;
	void clearBoard();

private:
	//members:
	std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
	std::vector<std::unique_ptr<MoveableObject>> m_moveableObjects;
	std::unique_ptr<LaserSource> m_laserSource;
	std::unique_ptr<Player> m_dog;
	std::unique_ptr<Player> m_cat;
	b2World* m_world;
	sf::Time m_levelTime;

	//private functions:
	sf::Vector2f calPosition(int, int);
	void createObject(char, int, int, char, ControlledObject*&);
	void checkIsAtHouse(House*, Player*);
};