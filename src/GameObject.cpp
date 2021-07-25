#include "GameObject.h"

GameObject::GameObject(sf::Sprite sprite, sf::Vector2f position, float widthRatio, float heightRatio)
	:m_dimensions(CELL_DIMENSIONS.x * widthRatio, CELL_DIMENSIONS.y * heightRatio), m_isAppear(true)
{
	sprite.setScale(m_dimensions.x / (sprite.getLocalBounds().width),
					m_dimensions.y / (sprite.getLocalBounds().height));

	sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

	sprite.setPosition(position);
	m_sprite = sprite;
}

bool GameObject::getIsAppear() const
{
	return m_isAppear;
}

void GameObject::draw(sf::RenderWindow& window)
{
	auto position = m_body->GetPosition();
	position *= PIXEL_METER_RATIO;
	m_sprite.setPosition(position.x, position.y);
	m_sprite.setRotation(m_body->GetAngle() * RADIAN_TO_DEGREE);
	animation();
	window.draw(m_sprite);
}

void GameObject::changeSprite(sf::Vector2i spriteIndexes, const sf::Vector2i size, type type, b2Vec2 side)
{
	m_sprite.setTextureRect(sf::IntRect(int((spriteIndexes.x * size.x) + PLAYER_PADDING.at(type)[0]) +
										int(PLAYER_PADDING.at(type)[1] * spriteIndexes.x),
										int((spriteIndexes.y * size.y) + PLAYER_PADDING.at(type)[2]) + 
										int(PLAYER_PADDING.at(type)[3] * spriteIndexes.y),
										size.x, size.y));
	m_sprite.setScale(m_dimensions.x / (m_sprite.getLocalBounds().width),
					  m_dimensions.y / (m_sprite.getLocalBounds().height));
	if (side == LEFT)
	{
		flipSprite();
	}
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
}

void GameObject::flipSprite()
{
	m_sprite.scale(-1.0f, 1.0f);
}

sf::Vector2f GameObject::getSpritePosition() const
{
	return m_sprite.getPosition();
}

sf::FloatRect GameObject::getSpriteGlobalBounds() const
{
	return m_sprite.getGlobalBounds();
}

void GameObject::addSensor(float x, float y, b2Vec2 position, float angle)
{
	b2PolygonShape polygonShape;
	b2FixtureDef myFixtureDef;
	myFixtureDef.shape = &polygonShape;
	myFixtureDef.density = 1;
	polygonShape.SetAsBox(x, y, position, angle);
	myFixtureDef.isSensor = true;
	myFixtureDef.filter.groupIndex = -1;
	b2Fixture* sensorFixture = m_body->CreateFixture(&myFixtureDef);
	sensorFixture->SetUserData((void*)1);
}

b2Body* GameObject::getBody()
{
	return m_body;
}

void GameObject::setBody(b2World& world, b2BodyType type, bool isSensor, bool isInGroup)
{
	b2BodyDef bodyDef;
	bodyDef.type = type;
	bodyDef.position.Set(m_sprite.getPosition().x / PIXEL_METER_RATIO, m_sprite.getPosition().y / PIXEL_METER_RATIO);
	m_body = world.CreateBody(&bodyDef);

	b2FixtureDef fixtureDef;
	b2PolygonShape polygonShape;
	b2CircleShape circleShape;

	if (!isInGroup)
	{
		polygonShape.SetAsBox(m_dimensions.x / (PIXEL_METER_RATIO * 2), m_dimensions.y / (PIXEL_METER_RATIO * 2));
		fixtureDef.shape = &polygonShape;
	}
	else
	{
		circleShape.m_radius = m_dimensions.y / (PIXEL_METER_RATIO * 2);
		fixtureDef.shape = &circleShape;
		fixtureDef.filter.groupIndex = -1;
	}

	fixtureDef.isSensor = isSensor;
	if (type == b2_dynamicBody)
	{
		fixtureDef.density = 1.f;
		fixtureDef.friction = 3.f;
	}

	m_body->CreateFixture(&fixtureDef);
	m_body->SetUserData(this);
}

void GameObject::setIsAppear(bool status)
{
	m_isAppear = status;
}