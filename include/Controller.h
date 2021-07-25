#pragma once

#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Pause.h"

class Controller
{
public:
	//d-tor:
	~Controller() = default;

	//access functions:
	void setIsRestart(bool);
	void setIsContinue(bool);
	std::array<bool, 3> getVictoryParameters(int);

	//other functions:
	static Controller& getController();
	bool run(sf::RenderWindow&, int);
	void clearBoard();

private:
	//c-tor:
	Controller();

	//memebers:
	Board m_board;
	sf::Sprite m_background;
	sf::Sprite m_sign;
	sf::Text m_text;
	sf::Clock m_timer;
	std::vector<std::array<bool, 3>> m_victoryParameters;
	bool m_isRestart;
	bool m_isContinue;
	Pause m_pause;

	//private functions:
	void draw(sf::RenderWindow&);
	void getKey();
	void victory(float, int);
};