#pragma once

#include "StaticObject.h"

class LaserSource : public StaticObject
{
public:
	//c-tor:
	LaserSource(sf::Vector2f, char, b2World&);

	//other functions:
	virtual object getObjectType() override { return object::laserSource; }
	void laser(b2World&);
	void laserRayCast(b2Vec2, b2Vec2, b2World&);
	virtual void draw(sf::RenderWindow&) override;

private:
	//members:
	static bool m_registerIt;
	std::vector<sf::VertexArray> m_laserRay;
	std::vector<sf::VertexArray> m_laserRayGlow;

	//private functions:
	void setLazerRayColor(sf::VertexArray&, sf::VertexArray&);
	void setLazerRayPosition(sf::VertexArray&, sf::VertexArray&, float, float, b2Vec2, b2Vec2);
};