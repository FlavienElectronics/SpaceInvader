#include "main.hpp"

// #define VERBOSE_MAIN

using namespace std;

class YouWon : public LetterGroup
{

};


struct main_info
{
	SpaceShip *ship;
	MonsterLine **monsters;
	bool **explosionVector;
};

void init(SpaceShip **ship, MonsterLine ***monsterL, bool ***explo, bool &allMonsDestroyed, bool &change, bool &shipDestroyed, int numberOfLine, sf::RenderWindow &win, float winH, float winW)
{
	shipDestroyed = false;
	*ship = new SpaceShip(&win, winH, winW, winW / 2, winH / 1.2, "Green");
	*monsterL = new MonsterLine *[numberOfLine];
	*explo = new bool *[numberOfLine];
	for (int i = 0; i < numberOfLine; i++)
	{
		(*explo)[i] = nullptr;
		(*monsterL)[i] = new MonsterLine(&win, winH, winW, winW / 2 - (1 + i * 2 * 4), winH / 2 - (1 + i * 2 * 4), i * 2 + 1, "col");
	}
	change = false;
	allMonsDestroyed = false;
}

void freeMem(SpaceShip *ship, MonsterLine **monsterL, bool **explo, int numberOfLine)
{
	delete ship;
	for (int j = 0; j < numberOfLine; j++)
	{
		delete monsterL[j];
		if (explo[j] != nullptr)
		{
			delete explo[j];
		}
	}
}

/*SpaceInvader INSA*/
int main()
{
	const string gameName = "SpaceInvader";
	const float windowWidth = 128;
	const float windowHeight = 64;
	// const float windowWidth = 1000;
	// const float windowHeight = 500;

	cout << "Window creation" << endl;
	sf::Vector2u resolution(windowWidth, windowHeight);
	sf::RenderWindow window(sf::VideoMode(resolution.x * 6, resolution.y * 6), gameName);
	sf::View view(sf::FloatRect(0, 0, resolution.x, resolution.y));
	view.setViewport(sf::FloatRect(0, 0, 1, 1));
	window.setView(view);

	int numberOfLine = 4;
	// int numberOfLine = 25;
	MonsterLine **mons;
	SpaceShip *ship;

	bool **explosion;
	bool change;
	bool shipDestroyed;

	bool allMonstersDestroyed;

	init(&ship, &mons, &explosion, allMonstersDestroyed, change, shipDestroyed, numberOfLine, window, windowHeight, windowWidth);

	sf::Clock clockCommand;
	sf::Clock clockProjectile;
	sf::Clock clockShoot;
	sf::Clock clockMonster;
	sf::Clock clockExplosion;
	sf::Clock clockRefreshScreen;
	sf::Time delayCommand = sf::milliseconds(10);
	sf::Time delayProjectile = sf::milliseconds(10);
	sf::Time delayMonster = sf::milliseconds(50);
	sf::Time delayShoot = sf::milliseconds(500);
	sf::Time delayExplosion = sf::milliseconds(150);
	sf::Time delayRefreshScreen = sf::milliseconds(17);

	sf::Event event;

	while (window.isOpen())
	{
		if (!shipDestroyed)
		{
			if (!allMonstersDestroyed)
			{
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}

				/*Managing the input command*/
				if (clockCommand.getElapsedTime() >= delayCommand)
				{

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
					{
						//cout << "Hide pixel" << endl;
						//ship->hidePixel(3,3);
					}

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					{
						try
						{
							ship->xAdd();
						}
						catch (SpaceShip::Exept exp)
						{
#ifdef VERBOSE_MAIN
							cout << exp.message << endl;
#endif
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					{
						try
						{
							ship->xSub();
						}
						catch (SpaceShip::Exept exp)
						{
#ifdef VERBOSE_MAIN
							cout << exp.message << endl;
#endif
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					{
						try
						{
							ship->yAdd();
						}
						catch (SpaceShip::Exept exp)
						{
#ifdef VERBOSE_MAIN
							cout << exp.message << endl;
#endif
						}
					}
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					{
						try
						{
							ship->ySub();
						}
						catch (SpaceShip::Exept exp)
						{
#ifdef VERBOSE_MAIN
							cout << exp.message << endl;
#endif
						}
					}

					for (int j = 0; j < numberOfLine; j++)
					{
						if (mons[j] != nullptr)
						{
							mons[j]->updateCollision(*ship, &(explosion[j]));
						}
					}

					shipDestroyed = ship->detectImpact(mons, numberOfLine);

					clockCommand.restart(); // Redémarre l'horloge pour le prochain intervalle
				}

				/*Managing the shooting*/
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (clockShoot.getElapsedTime() >= delayShoot)
					{
						ship->shoot();
						for (int j = 0; j < numberOfLine; j++)
						{
							for (int i = 0; i < mons[j]->getNumberOfMonster(); i++)
							{
								Monster &tempMonster = (*mons[j])[i];
								if (tempMonster.isAlive())
								{
									tempMonster.shoot();
								}
							}
						}
						clockShoot.restart(); // Redémarre l'horloge pour le prochain intervalle
					}
				}

				/*Managing the projectile*/
				if (clockProjectile.getElapsedTime() >= delayProjectile)
				{
					ship->updateProjectiles();
					for (int j = 0; j < numberOfLine; j++)
					{
						for (int i = 0; i < mons[j]->getNumberOfMonster(); i++)
						{
							Monster &tempMonster = (*mons[j])[i];
							tempMonster.updateProjectiles();
						}
					}
					clockProjectile.restart();
				}

				/*Managing the monsters's movement*/
				if (clockMonster.getElapsedTime() >= delayMonster)
				{
					for (int j = 0; j < numberOfLine; j++)
					{
						if (mons[j]->getDirection() == 0) // go left
						{
							try
							{
								mons[j]->xSub();
							}
							catch (SpaceShip::Exept &exp)
							{
								change = true;
								//cout << exp.message << endl;
							}
						}
						else if (mons[j]->getDirection() == 1) // go right
						{
							try
							{
								mons[j]->xAdd();
							}
							catch (SpaceShip::Exept &exp)
							{
								change = true;
								//cout << exp.message << endl;
							}
						}

						if (change)
						{
							mons[j]->changeDirection();
							change = false;
						}
					}

					/*Checking if all monsters are dead*/
					for (int i = 0; i < numberOfLine; i++)
					{
						if (!(mons[i]->isLineDestoyed()))
						{
							break;
						}
						else
						{
							if (i == (numberOfLine - 1))
							{
								allMonstersDestroyed = true;
							}
						}
					}

					clockMonster.restart();
				}

				/*Explosion management*/
				for (int j = 0; j < numberOfLine; j++)
				{
					if (explosion != nullptr)
					{
						if (explosion[j] != nullptr)
						{
							for (int i = 0; i < mons[j]->getNumberOfMonster(); i++)
							{
								// Check if we should update the explosion particles
								Monster &tempMonster = (*mons[j])[i];
								if (mons[j]->isExplosing(i) && tempMonster.getElapsedTimeClockExplosion() >= delayExplosion)
								{
									mons[j]->updateParticule(i);
									tempMonster.resetClockExplosion();
								}

								// Only trigger an explosion if needed and the monster is alive
								if (explosion[j][i] && mons[j]->isAlive(i))
								{
									mons[j]->explode(i); // Start explosion
									//cout << "Monster " << i << " in line " << j << " exploded." << endl;
									clockExplosion.restart(); // Only reset timer when an explosion starts
								}
							}
						}
					}
				}

				if (clockRefreshScreen.getElapsedTime() >= delayRefreshScreen)
				{
					// Erase the screen in white
					window.clear(sf::Color::White);

					/*Displaying ship and monsters*/
					window.draw(*ship);
					for (int j = 0; j < numberOfLine; j++)
					{
						for (int i = 0; i < mons[j]->getNumberOfMonster(); i++)
						{
							window.draw((*mons[j])[i]);
						}
					}
					window.display();
					clockRefreshScreen.restart();
				}
			}

			/*Player kills all the monster*/
			// Erase the screen in majenta
			else
			{
				cout << "All monster destroyed" << endl;
				if (clockRefreshScreen.getElapsedTime() >= delayRefreshScreen)
				{
					window.clear(sf::Color::Magenta);

					// window.draw(GameOver(windowWidth, windowHeight));

					window.display();
					clockRefreshScreen.restart();
				}
			}
		}
		else
		{
			cout << "Monsters killed you" << endl;
			if (clockRefreshScreen.getElapsedTime() >= delayRefreshScreen)
			{
				window.clear(sf::Color::Black);

				window.draw(GameOver(windowWidth, windowHeight));

				window.display();

				clockRefreshScreen.restart();
			}
		}

		/*Player died*/
		// Erase the screen in black

		if (clockCommand.getElapsedTime() >= delayCommand)
		{
			/*Reseting the game*/
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				freeMem(ship, mons, explosion, numberOfLine);
				init(&ship, &mons, &explosion, allMonstersDestroyed, change, shipDestroyed, numberOfLine, window, windowHeight, windowWidth);
			}
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	cout << "Window closed" << endl;

	freeMem(ship, mons, explosion, numberOfLine);

	return 0;
}
