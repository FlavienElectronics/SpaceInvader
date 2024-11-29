#ifndef MAIN_HPP
#define MAIN_HPP

#include <boost/asio.hpp>
#include <math.h>

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