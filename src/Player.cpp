#include "Player.h"

#include "Resources.h"
#include <unordered_map>
#include "Factory.h"
#include "Controller.h"

bool Player::m_registerIt = Factory<Player>::registerIt(PLAYER, [](sf::Vector2f position, char type, b2World& world) ->
	std::unique_ptr<Player> { return std::make_unique<Player>(position, type, world); });

Player::Player(sf::Vector2f position, char type, b2World& world)
	: MoveableObject(Resources::getResources().getSprite(initType(type)), sf::Vector2f(position.x, position.y),
					 HALF_RATIO, DOUBLE_RATIO),
		m_status(0,0), m_deltaTime(sf::seconds(0.1f)), m_side(RIGHT), m_isAtHouse(false), m_lastStatus(status::stand),
		m_footContacts(0)
{
	setBody(world, b2_dynamicBody, false, true);

	//add foot sensor fixture
	addSensor(FOOT_SENSOR_SIZE.x, FOOT_SENSOR_SIZE.y, b2Vec2(0, ((CELL_DIMENSIONS.y * DOUBLE_RATIO) / (PIXEL_METER_RATIO * 2))), 0);

	getBody()->SetFixedRotation(true);
	changeSprite(m_status, SIZE_OF_PLAYER.at(m_type), m_type, m_side);
	m_clock.restart();
}

void Player::move(b2Vec2 direction)
{
	auto impulseX = getBody()->GetMass() * (direction.x - getBody()->GetLinearVelocity().x);
	auto impulseY = getBody()->GetMass() * (direction.y - getBody()->GetLinearVelocity().y);

	if (direction == UP && m_footContacts > 0)
	{
		getBody()->ApplyLinearImpulse(b2Vec2(0, impulseY), getBody()->GetWorldCenter(), true);
		if (m_status.y != int(status::stand))
		{
			m_status = sf::Vector2i(0, int(status::stand));
		}
	}

	else if(direction == LEFT)
	{
		getBody()->ApplyLinearImpulse(b2Vec2(impulseX, 0), getBody()->GetWorldCenter(), true);
		m_side = LEFT;
		if (m_status.y != int(status::run))
		{
			m_status = sf::Vector2i(0, int(status::run));
		}
	}

	else if (direction == RIGHT)
	{
		getBody()->ApplyLinearImpulse(b2Vec2(impulseX, 0), getBody()->GetWorldCenter(), true);
		m_side = RIGHT;
		if (m_status.y != int(status::run))
		{
			m_status = sf::Vector2i(0, int(status::run));
		}
	}

	else
	{
		getBody()->ApplyLinearImpulse(b2Vec2(impulseX, 0), getBody()->GetWorldCenter(), true);
		if (m_status.y != int(status::stand))
		{
			m_status = sf::Vector2i(0, int(status::stand));
		}
	}
	
	if (getBody()->GetLinearVelocity().y < 0)
	{
		m_lastStatus = status::jump;
	}
	else if (getBody()->GetLinearVelocity().y > 0)
	{
		m_lastStatus = status::fall;
	}
	else if (getBody()->GetLinearVelocity().x != 0)
	{
		m_lastStatus = status::run;
	}
	else
	{
		m_lastStatus = status::stand;
	}
}

bool Player::getIsAtHouse() const
{
	return m_isAtHouse;
}

void Player::setIsAtHouse(bool status)
{
	m_isAtHouse = status;
}

status Player::getLastStatus() const
{
	return m_lastStatus;
}

void Player::incFootContacts()
{
	++m_footContacts;
}

void Player::decFootContacts()
{
	--m_footContacts;
}

void Player::startContact(Obstacle* obstacle)
{
	if ((obstacle->getType() != m_type || obstacle->getType() == type::blueObstacle) && m_lastStatus != status::jump)
	{
		setIsAppear(false);
		Resources::getResources().playSound(gameSounds::ohNo);
		Controller::getController().setIsRestart(true);
	}
}

void Player::startContact(Treat* treat)
{
	if (treat->getType() == m_type || treat->getType() == type::treats)
	{
		treat->setIsTaken(true);
		if (m_type == type::dog)
		{
			Resources::getResources().playSound(gameSounds::bark);
		}
		else
		{
			Resources::getResources().playSound(gameSounds::meow);
		}
	}
}

void Player::startContact(House* house)
{
	if (house->getType() == m_type)
	{
		m_isAtHouse = true;
		Resources::getResources().playSound(gameSounds::doorbell);
	}
}

void Player::startContact(Button* button)
{
	button->activateControlledObject();
}

void Player::startContact(Switch* switchObj)
{
	if (m_side == RIGHT)
	{
		switchObj->activateControlledObject();
	}
	else
	{
		switchObj->unactivateControlledObject();
	}
}

void Player::endContact(House* house)
{
	if (house->getType() == m_type)
	{
		m_isAtHouse = false;
	}
}

void Player::endContact(Button* button)
{
	button->unactivateControlledObject();
}

void Player::animation()
{
	if (m_deltaTime.asSeconds() - m_clock.getElapsedTime().asSeconds() <= 0)
	{
		m_status.x++;
		if (m_status.x == PLAYER_NUM_OF_SPRITES)
		{
			m_status.x = 0;
		}
		changeSprite(m_status, SIZE_OF_PLAYER.at(m_type), m_type, m_side);
		m_clock.restart();
	}
}

void Player::movement(b2Vec2 direction)
{
	auto impulseX = getBody()->GetMass() * (direction.x - getBody()->GetLinearVelocity().x);
	auto impulseY = getBody()->GetMass() * (direction.y - getBody()->GetLinearVelocity().y);

	getBody()->ApplyLinearImpulseToCenter(b2Vec2(impulseX, impulseY), true);
}

type Player::initType(char type)
{
	switch (type)
	{
	case OF_DOG:
		m_type = type::dog;
		return type::dog;
		break;

	case OF_CAT:
		m_type = type::cat;
		return type::cat;
		break;

	default:
		throw std::invalid_argument("Invalid input!");
		break;
	}
}
