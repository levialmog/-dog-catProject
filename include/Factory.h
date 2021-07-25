#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <memory>

template <class T>
class Factory
{
public:
	//c-tor:
	Factory() = default;

	//d-tor:
	~Factory() = default;

	//other functions:
	using funcPtr = std::unique_ptr<T>(*)(sf::Vector2f, char, b2World&);
	static std::unique_ptr<T> create(char, sf::Vector2f, char, b2World&);
	static bool registerIt(char, funcPtr);

private:
	//private functions:
	static auto& getMap()
	{
		static std::map<char, funcPtr> map;
		return map;
	}
};

template <class T>
std::unique_ptr<T> Factory<T>::create(char object, sf::Vector2f position, char type, b2World& world)
{
	auto it = Factory<T>::getMap().find(object);
	if (it == Factory<T>::getMap().end())
	{
		return nullptr;
	}
	return it->second(position, type, world);
}

template <class T>
bool Factory<T>::registerIt(char object, funcPtr f)
{
	Factory<T>::getMap().emplace(object, f);
	return true;
}