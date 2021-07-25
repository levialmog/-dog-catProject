#pragma once

#include "GameObject.h"
#include <typeinfo>
#include <typeindex>
#include <map>

using HitFunctionPtr = void (*)(GameObject*, GameObject*);
using Key = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<Key, HitFunctionPtr>;

class CollisionHandler
{
public:
	//d-tor:
	~CollisionHandler() = default;

	//other functions:
	static CollisionHandler& getCollisionHandler();
	void processCollision(GameObject*, GameObject*, bool);

private:
	//c-tor:
	CollisionHandler() = default;

	//private functions:
	HitFunctionPtr lookup(const std::type_index&, const std::type_index&, bool);
	HitMap initializeStartCollisionMap();
	HitMap initializeEndCollisionMap();
};