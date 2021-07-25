#pragma once

#include "MoveableObject.h"
#include "Treat.h"
#include "House.h"
#include "Button.h"
#include "Switch.h"
#include "Obstacle.h"
#include "Floor.h"

class Player : public MoveableObject
{
public:
	//c-tors:
	Player(sf::Vector2f, char, b2World&);

	//access functions:
	bool getIsAtHouse() const;
	void setIsAtHouse(bool);
	status getLastStatus() const;
	void incFootContacts();
	void decFootContacts();

	//other functions:
	void move(b2Vec2);
	virtual object getObjectType() override { return object::player; }
	
	//collion functions: 
	void startContact(Obstacle*);
	void startContact(Treat*);
	void startContact(House*);
	void startContact(Button*);
	void startContact(Switch*);

	void endContact(House*);
	void endContact(Button*);

private:
	//members:
	sf::Clock m_clock;
	sf::Time m_deltaTime;
	sf::Vector2i m_status;
	type m_type;
	b2Vec2 m_side;
	bool m_isAtHouse;
	status m_lastStatus;
	static bool m_registerIt;
	int m_footContacts;

	//private functions:
	virtual void animation() override;
	void movement(b2Vec2);
	type initType(char);
};