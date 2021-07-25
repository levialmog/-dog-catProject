#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <unordered_map>
#include <string>
#include <Box2D/box2D.h>

const auto BOARD_DIMENSIONS = sf::Vector2i(18, 18);
const auto WINDOW_DIMENSIONS = sf::Vector2i(1800, 900);
const auto CELL_DIMENSIONS = sf::Vector2f(float(WINDOW_DIMENSIONS.x) / BOARD_DIMENSIONS.x,
										  float(WINDOW_DIMENSIONS.y) / BOARD_DIMENSIONS.y);
const auto MAIN_MENU_DIMENSIONS = sf::Vector2f(300.f, float(WINDOW_DIMENSIONS.y / 2));
const auto LEVEL_MENU_DIMENSIONS = sf::Vector2f(float(WINDOW_DIMENSIONS.x), float(WINDOW_DIMENSIONS.y / 2));
const auto MAIN_MENU_BUTTON_DIMENSIONS = sf::Vector2f(300, 100);
const auto SMALL_BUTTON_DIMENSIONS = sf::Vector2f(100, 100);
const auto VICTORY_PARAMETER_DIMENSIONS = sf::Vector2f(60, 60);

const auto NUM_OF_LEVELS = 4;
const auto LEVELS_BUTTON_PADDING = ((WINDOW_DIMENSIONS.x - (SMALL_BUTTON_DIMENSIONS.x * NUM_OF_LEVELS)) / (NUM_OF_LEVELS +1));
const auto PAUSE_MENU_BUTTON_PADDING = ((WINDOW_DIMENSIONS.x - (SMALL_BUTTON_DIMENSIONS.x * 3)) / 8);

const char PLAYER = 'P';
const char FLOOR = '-';
const char TREAT = '*';
const char BOX = '#';
const char MIRROR_BOX = 'M';
const char LASER_SOURCE = 'L';
const char LASER_DESTINATION = 'D';
const char SWITCH = 'S';
const char BUTTON = '@';
const char GATE = '|';
const char HOUSE = 'H';
const char R_A_MIRROR = 'Q';
const char OBSTACLE = '~';
const char EMPTY = ' ';
const char BLUE = 'b';
const char RED = 'r';
const char GREEN = 'g';
const char PURPLE = 'p';
const char YELLOW = 'y';
const char OF_DOG = 'd';
const char OF_CAT = 'c';
const char OF_EVERYONE = 'e';

const b2Vec2 UP(0, -5.5);
const b2Vec2 RIGHT(3, 0);
const b2Vec2 LEFT(-3, 0);
const b2Vec2 STAND(0, 0);

enum class status
{
	stand,
	run,
	jump,
	fall
};
enum class state
{
	menu,
	game,
	instructions
};
enum class menu
{
	play,
	help,
	exit,
	pause,
	levels,
	restart,
	resume,
	homeMenu,
	startLevel
};
enum class object
{
	button,
	box,
	floorTile,
	gate,
	house,
	laserDestination,
	laserSource,
	mirrorBox,
	obstacle,
	player,
	rightAngleMirror,
	switchObject,
	treat
};
enum class type
{
	background,
	blueButton,
	blueGate,
	blueObstacle,
	bone,
	box,
	cat,
	catHouse,
	clockIcon,
	dog,
	dogCatIcon,
	dogHouse,
	exitButton,
	fish,
	floorTile,
	grayObstacle,
	greenGate,
	greenRightAngleMirror,
	greenSwitch,
	helpButton,
	homeButton,
	instructions,
	laserDestination,
	laserSource,
	levelsButton,
	menuBackground,
	menuButton,
	mirrorBox,
	orangeObstacle,
	pauseButton,
	playButton,
	purpleGate,
	purpleRightAngleMirror,
	purpleSwitch,
	redButton,
	redGate,
	restartButton,
	resumeButton,
	sign,
	treats,
	yellowGate
};

enum class gameSounds
{
	backgroundMusic,
	bark,
	click,
	doorbell,
	meow,
	ohNo,
	win
};

const int PLAYER_NUM_OF_SPRITES = 10;
const std::unordered_map<type, sf::Vector2i> SIZE_OF_PLAYER = { {type::dog, sf::Vector2i(292, 452)},
																{type::cat, sf::Vector2i(287, 431)} };
const std::unordered_map<type, std::array<float, 4>> PLAYER_PADDING = { {type::dog, {105, 255, 17, 33}},
																		{type::cat, {105, 255, 29, 38}} };

const float EIGHTH_RATIO = 0.125f,
			QUARTER_RATIO = 0.25f,
			HALF_RATIO = 0.5f,
			ONE_AND_HALF_RATIO = 1.5f,
			DOUBLE_RATIO = 1.9f,
			STANDARD_RATIO = 1.f,
			PIXEL_METER_RATIO = 100.f,
			DEGREE_TO_RADIAN = (b2_pi / 180),
			RADIAN_TO_DEGREE = (180 / b2_pi),
			DIFF = 5.f;

const auto FOOT_SENSOR_SIZE = b2Vec2(0.1f, 0.1f);
const float MIRROR_ANGLE = 45,
			ROTATE_ANGLE = 90,
			EPSILON = 0.5;
