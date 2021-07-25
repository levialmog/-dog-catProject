#pragma once

#include "GameObject.h"

class StaticObject : public GameObject
{
public:
	//c-tor:
	StaticObject(sf::Sprite, sf::Vector2f, float = 1, float = 1);
};