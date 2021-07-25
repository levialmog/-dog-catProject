
#include <fstream>
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "Macros.h"
#include "Play.h"
#include "Help.h"
#include "Exit.h"
#include "Resources.h"

int main() try
{
	Resources::getResources().playMusic();

	auto window = sf::RenderWindow(sf::VideoMode(WINDOW_DIMENSIONS.x, WINDOW_DIMENSIONS.y), "Dog & Cat");
	window.setPosition({ 0,0 });
	window.setFramerateLimit(60);

	auto mainMenu = Menu();

	mainMenu.add(menu::play, std::make_unique<Play>());
	mainMenu.add(menu::help, std::make_unique<Help>());
	mainMenu.add(menu::exit, std::make_unique<Exit>());

	mainMenu.activate(window);
}
catch (std::exception& e)
{
	std::ofstream logfile;
	logfile.open("log.txt");
	logfile << e.what() << std::endl;
	logfile.close();

	return EXIT_FAILURE;
}
catch (...)
{
	std::ofstream logfile;
	logfile.open("log.txt");
	logfile << "Unknown exception!" << std::endl;
	logfile.close();

	return EXIT_FAILURE;
}