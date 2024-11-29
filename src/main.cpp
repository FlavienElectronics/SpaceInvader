#include "main.hpp"
#include "main_function.hpp"

using namespace std;

void gameOver(main_info &main_information, clock_info &clock_information)
{
	if (main_information.endScreenPrinted == false)
	{
		/*Check if the player pressed the button to restart the game*/

		if (clock_information.clockRefreshScreen.getElapsedTime() >= clock_information.delayRefreshScreen)
		{
			main_information.endScreenPrinted = true; // Display only once per game
			cout << "Monsters killed you" << endl;
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
	}

	if (main_information.uControler.isConnected())
	{
		ESP::USART_package localPackage;
		localPackage = main_information.uControler.readUSART();
		if (localPackage.device == "BTN")
			init(main_information);
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

void youWon(main_info &main_information, clock_info &clock_information)
{
	if (main_information.endScreenPrinted == false)
	{

		if (clock_information.clockRefreshScreen.getElapsedTime() >= clock_information.delayRefreshScreen)
		{
			main_information.endScreenPrinted = true; // Display only once per game
			cout << "All monster destroyed" << endl;
			main_information.win.clear(sf::Color::Magenta);

			main_information.win.draw(YouWon("B", main_information.winW, main_information.winH));

			main_information.win.display();
			clock_information.clockRefreshScreen.restart();
		}
	}
	/*Check if the player pressed the button to restart the game*/
	if (main_information.uControler.isConnected())
	{
		ESP::USART_package localPackage;
		localPackage = main_information.uControler.readUSART();
		if (localPackage.device == "BTN")
			init(main_information);
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

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*UNTESTED !!!!!! NEED TO TEST WITH ESP8266*/
void manage_uControler(main_info &main_information, clock_info &clock_information)
{
	/* Reading USART and sending command to game */
	if (main_information.uControler.isConnected())
	{
		int totalMonsterAlive = 0;
		for (int t = 0; t < main_information.numberOfLine; t++)
		{
			totalMonsterAlive += (*main_information.monsterL)[t]->getNumberOfMonsterAlive();
		}
		string messageToESP = "[SCR]";
		messageToESP += to_string((int)pow(2, main_information.numberOfLine) - totalMonsterAlive);
		main_information.uControler.sendUSART(messageToESP);

		ESP::USART_package localPackage;
		localPackage = main_information.uControler.readUSART();
		// cout << localPackage.value << endl;
		if (localPackage.device == "POT")
		{
			int position = main_information.winW * (localPackage.value) / 100;
			(*main_information.ship)->goTo(position - 1);
		}
		else if (localPackage.device == "BTN")
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
}
/*UNTESTED !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! 485 897897/*-+ ++++++++++++9+9---+-++-+--++//+//+*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/

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

	/*remove that*/
	/*---d-fsd-sd-f-sdf-sdf-sd-fs-df-sdf-sd-fsd-f-sdfs*/
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

				manage_uControler(main_info, clock_info);

				/*Managing the input command*/
				/* Update collision and detect impact between projectile and ship-monster*/
				if (clock_info.clockCommand.getElapsedTime() >= clock_info.delayCommand)
				{
					manageKeyboard(main_info, clock_info);

					updateCollision(main_info);

					detectImpact(main_info);

					clock_info.clockCommand.restart(); // Redémarre l'horloge pour le prochain intervalle
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
				youWon(main_info, clock_info);
			}
		}
		/*Player died*/
		// Erase the screen in black
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