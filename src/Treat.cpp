#include "Treat.h"

#include "Resources.h"
#include "Factory.h"

bool Treat::m_registerIt = Factory<StaticObject>::registerIt(TREAT, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<StaticObject> { return std::make_unique<Treat>(position, type, world); });

int Treat::m_numOfTreats = 0;

Treat::Treat(sf::Vector2f position, char type, b2World& world)
	:StaticObject(Resources::getResources().getSprite(initType(type)), position, HALF_RATIO, HALF_RATIO), m_isTaken(false)
{
	setBody(world, b2_staticBody, true, false);
	++m_numOfTreats;
}

Treat::~Treat()
{
	--m_numOfTreats;
	getBody()->GetWorld()->DestroyBody(getBody());
}

type Treat::getType() const
{
	return m_type;
}

bool Treat::getIsTaken() const
{
	return m_isTaken;
}

void Treat::setIsTaken(bool status)
{
	m_isTaken = status;
}

int Treat::getNumOfTreats()
{
	return m_numOfTreats;
}

type Treat::initType(char type)
{
	switch (type)
	{
	case OF_DOG:
		m_type = type::dog;
		return type::bone;
		break;

	case OF_CAT:
		m_type = type::cat;
		return type::fish;
		break;
	
	case OF_EVERYONE:
		m_type = type::treats;
		return type::treats;
		break;
		
	default:
		throw std::invalid_argument("Invalid input!");
		break;
	}
}
