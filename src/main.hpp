/**
 * @file MAIN.hpp
 * @brief Declaration of structures and includes for managing the main game logic, communication with ESP, and game states.
 * 
 * This header file contains the structure declarations and the necessary includes for managing the
 * overall game logic, including the spaceship, monsters, projectiles, and explosion effects.
 * It also integrates communication with an external ESP device through the `ESP` class for control input,
 * as well as the setup for game state management such as victory, defeat, and ongoing game processes.
 * Additionally, it defines the `main_info` and `clock_info` structures that handle communication and time tracking.
 * 
 * @version 1.0
 * @date 2024-12-08
 */

#ifndef MAIN_HPP
#define MAIN_HPP

#include <boost/asio.hpp>
#include <math.h>
#include <thread>

#include <vector>

#include "Point.hpp"
#include "SpaceShip.hpp"
#include "Monster.hpp"
#include "Projectile.hpp"
#include "Explosion.hpp"
#include "MonsterLine.hpp"
#include "GameOver.hpp"
#include "YouWon.hpp"
#include "ESP.hpp"

struct communication_ESP
{
	string requestedFunction;
	float position;
	bool functionRequested_OK;
};

struct main_info
{
	ESP &uControler;
	sf::RenderWindow &win;
	SpaceShip **ship;
	MonsterLine ***monsterL;
	bool ***explo;
	bool allMonsDestroyed;
	bool change;
	bool shipDestroyed;
	int numberOfLine;
	float winH;
	float winW;
    bool endScreenPrinted;
	struct communication_ESP package_ESP;
};

struct clock_info
{
	sf::Clock clockCommand;
	sf::Clock clockProjectile;
	sf::Clock clockShoot;
	sf::Clock clockMonster;
	sf::Clock clockExplosion;
	sf::Clock clockRefreshScreen;
	sf::Time delayCommand;
	sf::Time delayProjectile;
	sf::Time delayMonster;
	sf::Time delayShoot;
	sf::Time delayExplosion;
	sf::Time delayRefreshScreen;
};

#endif