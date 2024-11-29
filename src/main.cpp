#include "main.hpp"

// #define VERBOSE_MAIN

using namespace std;

struct main_info
{
	ESP &uControler;
	SpaceShip **ship;
	MonsterLine ***monsterL;
	bool ***explo;
	bool &allMonsDestroyed;
	bool &change;
	bool &shipDestroyed;
	int numberOfLine;
	sf::RenderWindow &win;
	float winH;
	float winW;
};

struct clock_info
{
	sf::Clock &clockCommand;
	sf::Clock &clockProjectile;
	sf::Clock &clockShoot;
	sf::Clock &clockMonster;
	sf::Clock &clockExplosion;
	sf::Clock &clockRefreshScreen;
	sf::Time &delayCommand;
	sf::Time &delayProjectile;
	sf::Time &delayMonster;
	sf::Time &delayShoot;
	sf::Time &delayExplosion;
	sf::Time &delayRefreshScreen;
};

void init(struct main_info &main_information)
{
	main_information.shipDestroyed = false;
	*main_information.ship = new SpaceShip(&main_information.win, main_information.winH, main_information.winW, main_information.winW / 2, main_information.winH / 1.2, "col");
	*main_information.monsterL = new MonsterLine *[main_information.numberOfLine];
	*main_information.explo = new bool *[main_information.numberOfLine];
	for (int i = 0; i < main_information.numberOfLine; i++)
	{
		(*main_information.explo)[i] = nullptr;
		(*main_information.monsterL)[i] = new MonsterLine(&main_information.win, main_information.winH, main_information.winW, main_information.winW / 2 - (1 + i * 2 * 4), main_information.winH / 2 - (1 + i * 2 * 4), i * 2 + 1, "col");
	}
	main_information.change = false;
	main_information.allMonsDestroyed = false;

	/* Sending to esp the initialisation signal*/
	if (main_information.uControler.isConnected())
	{
		string messageToESP = "[RST]";
		main_information.uControler.sendUSART(messageToESP);
	}
}

/*Delete monsters line allocated, ship allocated and explosion bool vector*/
void freeMem(main_info &main_information)
{
	// Delete allocated ship
	delete (*main_information.ship);
	// Delete allocated monsters line
	for (int j = 0; j < main_information.numberOfLine; j++)
	{
		delete (*main_information.monsterL)[j];

		// Delete allocated bool vector
		if ((*main_information.explo)[j] != nullptr)
		{
			delete (*main_information.explo)[j];
		}
	}
}

void manageKeyboard(main_info &main_information, clock_info &clock_information)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		try
		{
			(*main_information.ship)->xAdd();
		}
		catch (SpaceShip::Exept exp)
		{
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		try
		{
			(*main_information.ship)->xSub();
		}
		catch (SpaceShip::Exept exp)
		{
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		try
		{
			(*main_information.ship)->yAdd();
		}
		catch (SpaceShip::Exept exp)
		{
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		try
		{
			(*main_information.ship)->ySub();
		}
		catch (SpaceShip::Exept exp)
		{
		}
	}

	/*Managing the shooting*/
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (clock_information.clockShoot.getElapsedTime() >= clock_information.delayShoot)
		{
			(*main_information.ship)->shoot();
			for (int j = 0; j < main_information.numberOfLine; j++)
			{
				for (int i = 0; i < (*main_information.monsterL)[j]->getNumberOfMonster(); i++)
				{
					Monster &tempMonster = (*(*main_information.monsterL)[j])[i];
					if (tempMonster.isAlive())
					{
						tempMonster.shoot();
					}
				}
			}
			clock_information.clockShoot.restart(); // Redémarre l'horloge pour le prochain intervalle
		}
	}
}

void updateCollision(main_info &main_information)
{
	for (int j = 0; j < main_information.numberOfLine; j++)
	{

		if ((*main_information.monsterL)[j] != nullptr)
		{
			(*main_information.monsterL)[j]->updateCollision(*(*main_information.ship), &(*main_information.explo)[j]);
		}
	}
}

void detectImpact(main_info &main_information)
{
	main_information.shipDestroyed = (*main_information.ship)->detectImpact((*main_information.monsterL), main_information.numberOfLine);
}

void updateProjectile(main_info &main_information, clock_info &clock_information)
{
	/*Managing the projectile*/
	if (clock_information.clockProjectile.getElapsedTime() >= clock_information.delayProjectile)
	{
		(*main_information.ship)->updateProjectiles();
		for (int j = 0; j < main_information.numberOfLine; j++)
		{
			for (int i = 0; i < (*main_information.monsterL)[j]->getNumberOfMonster(); i++)
			{
				Monster &tempMonster = (*(*main_information.monsterL)[j])[i];
				tempMonster.updateProjectiles();
			}
		}
		clock_information.clockProjectile.restart();
	}
}

void manageMonsters(main_info &main_information, clock_info clock_information)
{
	/*Managing the monsters's movement*/
	if (clock_information.clockMonster.getElapsedTime() >= clock_information.delayMonster)
	{
		for (int j = 0; j < main_information.numberOfLine; j++)
		{
			if ((*main_information.monsterL)[j]->getDirection() == 0) // go left
			{
				try
				{
					(*main_information.monsterL)[j]->xSub();
				}
				catch (SpaceShip::Exept &exp)
				{
					main_information.change = true;
				}
			}
			else if ((*main_information.monsterL)[j]->getDirection() == 1) // go right
			{
				try
				{
					(*main_information.monsterL)[j]->xAdd();
				}
				catch (SpaceShip::Exept &exp)
				{
					main_information.change = true;
				}
			}

			if (main_information.change)
			{
				(*main_information.monsterL)[j]->changeDirection();
				main_information.change = false;
			}
		}

		/*Checking if all monsters are dead*/
		for (int i = 0; i < main_information.numberOfLine; i++)
		{
			if (!(*main_information.monsterL)[i]->isLineDestoyed())
			{
				break;
			}
			else
			{
				if (i == (main_information.numberOfLine - 1))
				{
					main_information.allMonsDestroyed = true;
				}
			}
		}

		clock_information.clockMonster.restart();
	}
}

void manageExplosion(main_info &main_information, clock_info clock_information)
{
	/*Explosion management*/
	for (int j = 0; j < main_information.numberOfLine; j++)
	{
		if (*main_information.explo != nullptr)
		{
			if ((*main_information.explo)[j] != nullptr)
			{
				for (int i = 0; i < (*main_information.monsterL)[j]->getNumberOfMonster(); i++)
				{
					// Check if we should update the explosion particles
					Monster &tempMonster = (*(*main_information.monsterL)[j])[i];
					if ((*main_information.monsterL)[j]->isExplosing(i) && tempMonster.getElapsedTimeClockExplosion() >= clock_information.delayExplosion)
					{
						(*main_information.monsterL)[j]->updateParticule(i);
						tempMonster.resetClockExplosion();
					}

					// Only trigger an explosion if needed and the monster is alive
					if ((*main_information.explo)[j][i] && (*main_information.monsterL)[j]->isAlive(i))
					{
						(*main_information.monsterL)[j]->explode(i); // Start explosion
						// cout << "Monster " << i << " in line " << j << " exploded." << endl;
						clock_information.clockExplosion.restart(); // Only reset timer when an explosion starts
					}
				}
			}
		}
	}
}

/*SpaceInvader INSA*/
int main()
{
	const string portName = "/dev/ttyUSB0";
	const unsigned int baud_rate = 921600;
	const string gameName = "SpaceInvader";
	const float windowWidth = 128;
	const float windowHeight = 64;

	ESP myESP(portName, baud_rate);

	cout << "Window creation" << endl;
	sf::Vector2u resolution(windowWidth, windowHeight);
	sf::RenderWindow window(sf::VideoMode(resolution.x * 6, resolution.y * 6), gameName);
	sf::View view(sf::FloatRect(0, 0, resolution.x, resolution.y));
	view.setViewport(sf::FloatRect(0, 0, 1, 1));
	window.setView(view);

	int numberOfLine = 4;
	MonsterLine **mons;
	SpaceShip *ship;

	bool **explosion;
	bool change;
	bool shipDestroyed;

	bool allMonstersDestroyed;
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

	struct main_info main_info = {myESP,
								  &ship,
								  &mons,
								  &explosion,
								  allMonstersDestroyed,
								  change,
								  shipDestroyed,
								  numberOfLine,
								  window,
								  windowHeight,
								  windowWidth};

	struct clock_info clock_info =
		{
			clockCommand,
			clockProjectile,
			clockShoot,
			clockMonster,
			clockExplosion,
			clockRefreshScreen,
			delayCommand,
			delayProjectile,
			delayMonster,
			delayShoot,
			delayExplosion,
			delayRefreshScreen};

	init(main_info);

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

				/* Reading USART and sending command to game */
				if (myESP.isConnected())
				{
					int totalMonsterAlive = 0;
					for (int t = 0; t < numberOfLine; t++)
					{
						totalMonsterAlive += mons[t]->getNumberOfMonsterAlive();
					}
					// temp+=totalMonsterAlive;
					string messageToESP = "[SCR]";
					messageToESP += to_string((int)pow(2, numberOfLine) - totalMonsterAlive);
					myESP.sendUSART(messageToESP);
					// cout << totalMonsterAlive << endl;

					ESP::USART_package localPackage;
					localPackage = myESP.readUSART();
					// cout << localPackage.value << endl;
					if (localPackage.device == "POT")
					{
						int position = windowWidth * (localPackage.value) / 100;
						ship->goTo(position - 1);
					}
					else if (localPackage.device == "BTN")
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
				}

				/*Managing the input command*/
				/* Update collision and detect impact between projectile and ship-monster*/
				if (clockCommand.getElapsedTime() >= delayCommand)
				{
					manageKeyboard(main_info, clock_info);

					updateCollision(main_info);

					detectImpact(main_info);

					clockCommand.restart(); // Redémarre l'horloge pour le prochain intervalle
				}

				updateProjectile(main_info, clock_info);

				manageMonsters(main_info, clock_info);

				manageExplosion(main_info, clock_info);

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
				/*Check if the player pressed the button to restart the game*/
				if (myESP.isConnected())
				{
					ESP::USART_package localPackage;
					localPackage = myESP.readUSART();
					if (localPackage.device == "BTN")
						init(main_info);
				}

				cout << "All monster destroyed" << endl;
				if (clockRefreshScreen.getElapsedTime() >= delayRefreshScreen)
				{
					window.clear(sf::Color::Magenta);

					window.draw(YouWon("B", windowWidth, windowHeight));

					window.display();
					clockRefreshScreen.restart();
				}
			}
		}
		else
		{
			/*Check if the player pressed the button to restart the game*/
			if (myESP.isConnected())
			{
				ESP::USART_package localPackage;
				localPackage = myESP.readUSART();
				if (localPackage.device == "BTN")
					init(main_info);
			}

			/*Player died*/
			// Erase the screen in black
			cout << "Monsters killed you" << endl;
			if (clockRefreshScreen.getElapsedTime() >= delayRefreshScreen)
			{
				window.clear(sf::Color::Black);
				ship->die();

				if (myESP.isConnected())
				{
					string messageToESP = "[GOR]";
					myESP.sendUSART(messageToESP);
				}

				window.draw(GameOver("W", windowWidth, windowHeight));

				window.display();

				clockRefreshScreen.restart();
			}
		}

		if (clockCommand.getElapsedTime() >= delayCommand)
		{
			/*Reseting the game*/
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				freeMem(main_info);
				init(main_info);
			}
		}

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	cout << "Window closed" << endl;

	freeMem(main_info);

	return 0;
}