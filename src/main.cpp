#include "main.hpp"
#include "main_function.hpp"

using namespace std;

void gameOver(main_info main_information, clock_info clock_information)
{
	/*Check if the player pressed the button to restart the game*/
	if (main_information.uControler.isConnected())
	{
		ESP::USART_package localPackage;
		localPackage = main_information.uControler.readUSART();
		if (localPackage.device == "BTN")
			init(main_information);
	}

	/*Player died*/
	// Erase the screen in black
	cout << "Monsters killed you" << endl;
	if (clock_information.clockRefreshScreen.getElapsedTime() >= clock_information.delayRefreshScreen)
	{
		main_information.win.clear(sf::Color::Black);
		(*main_information.ship)->die();

		if (main_information.uControler.isConnected())
		{
			string messageToESP = "[GOR]";
			main_information.uControler.sendUSART(messageToESP);
		}

		main_information.win.draw(GameOver("W", main_information.winW, main_information.winH));

		main_information.win.display();

		clock_information.clockRefreshScreen.restart();
	}

	if (clock_information.clockCommand.getElapsedTime() >= clock_information.delayCommand)
	{
		/*Reseting the game*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		{
			freeMem(main_information);
			init(main_information);
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

				displayGame(main_info, clock_info);
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
			gameOver(main_info, clock_info);
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