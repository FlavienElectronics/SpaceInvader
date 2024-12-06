#include "main.hpp"
#include "main_function.hpp"
#include <thread>
#include <mutex>

using namespace std;

/*SpaceInvader INSA*/
int main()
{
	/*Configuration of the ESP8266's connection*/
	const string portName = "/dev/port_ESP8266";
	const unsigned int baud_rate = 921600;

	/*Configuration of the windows*/
	const string gameName = "SpaceInvader";
	const float windowWidth = 128;
	const float windowHeight = 64;
	sf::Vector2u resolution(windowWidth, windowHeight);
	sf::RenderWindow window(sf::VideoMode(resolution.x * 6, resolution.y * 6), gameName);
	sf::View view(sf::FloatRect(0, 0, resolution.x, resolution.y));
	view.setViewport(sf::FloatRect(0, 0, 1, 1));
	window.setView(view);
	cout << "Window creation" << endl;

	sf::Event event;

	/*Contruction of an object of type ESP
	It establish the connection if the uControler is connected
	*/
	ESP myESP(portName, baud_rate);

	struct clock_info clock_info;

	struct main_info main_info = {myESP, window};
	main_info.winW = windowWidth;
	main_info.winH = windowHeight;
	main_info.numberOfLine = 4;

	/*Initialisation of the mains variables and allocation*/
	init(main_info, clock_info);

	// std::thread uControllerThread(manage_uControler,std::ref(main_info),std::ref(clock_info));
	std::thread uControllerThread(manage_uControler, std::ref(main_info), std::ref(clock_info));

	/*Check if the windows is still open*/
	while (window.isOpen())
	{
		if (!main_info.shipDestroyed)
		{
			if (!main_info.allMonsDestroyed)
			{
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						window.close();
				}

				if (!main_info.package_ESP.functionRequested_OK)
				{
					if (main_info.package_ESP.requestedFunction == "BTN")
					{
						(*main_info.ship)->shoot();
						for (int j = 0; j < main_info.numberOfLine; j++)
						{
							for (int i = 0; i < (*main_info.monsterL)[j]->getNumberOfMonster(); i++)
							{
								Monster &tempMonster = (*(*main_info.monsterL)[j])[i];
								if (tempMonster.isAlive())
								{
									tempMonster.shoot();
								}
							}
						}
						main_info.package_ESP.functionRequested_OK = true;
					}
					else if (main_info.package_ESP.requestedFunction == "POT")
					{
						(*main_info.ship)->goTo(main_info.package_ESP.position);
						main_info.package_ESP.functionRequested_OK = true;
					}
				}

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

			/*The player had killed all the monsters*/
			// Erases the screen in majenta and displays the winning screen
			else
			{
				youWon(main_info, clock_info);
			}
		}
		/*The player died*/
		// Erase the screen in black
		else
		{
			gameOver(main_info, clock_info);
		}

		/*Checks if the user closed the windows*/
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	cout << "Window closed" << endl;

	uControllerThread.join();

	/*Free the memory allocated*/
	freeMem(main_info);

	return 0;
}