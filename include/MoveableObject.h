#pragma once

#include "GameObject.h"

class MoveableObject : public GameObject
{
public:
	//c-tors:
	MoveableObject() = default;
	MoveableObject(sf::Sprite, sf::Vector2f, float = 1, float = 1);
};