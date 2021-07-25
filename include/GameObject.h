#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Macros.h"

class GameObject
{
public:
	//c-tors:
	GameObject() { m_body = nullptr; m_isAppear = true; };
	GameObject(sf::Sprite, sf::Vector2f, float = 1, float = 1);

	//d-tor:
	virtual ~GameObject() = default;

	//access functions:
	bool getIsAppear() const;

	//other functions:
	virtual void animation() {};
	virtual void draw(sf::RenderWindow&);
	void changeSprite(sf::Vector2i, const sf::Vector2i, type, b2Vec2);
	virtual object getObjectType() = 0;
	void flipSprite();
	sf::Vector2f getSpritePosition() const;
	sf::FloatRect getSpriteGlobalBounds() const;
	void addSensor(float, float, b2Vec2, float);

protected:
	b2Body* getBody();
	void setBody(b2World&, b2BodyType, bool, bool);
	void setIsAppear(bool);

private:
	//members:
	sf::Sprite m_sprite;
	sf::Vector2f m_dimensions;
	b2Body* m_body;
	bool m_isAppear;
};