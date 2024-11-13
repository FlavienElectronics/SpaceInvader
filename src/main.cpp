#include "main.hpp"

// #define VERBOSE_MAIN

using namespace std;

/*SpaceInvader INSA*/
int main()
{
	const string gameName = "SpaceInvader";
	const float windowWidth = 128;
	const float windowHeight = 96;

	// Création de la fenêtre SFML
	cout << "Window creation" << endl;
	sf::Vector2u resolution(windowWidth, windowHeight);
	// Créez une fenêtre avec une taille agrandie
	sf::RenderWindow window(sf::VideoMode(resolution.x * 6, resolution.y * 6), gameName);
	// Créez une vue qui correspond à la résolution de départ
	sf::View view(sf::FloatRect(0, 0, resolution.x, resolution.y));
	// Appliquez l’échelle à la vue (par exemple, x2 pour doubler la taille)
	view.setViewport(sf::FloatRect(0, 0, 1, 1)); // Fenêtre entière
	window.setView(view);
	float x = windowWidth / 2, y = windowHeight / 2; // Position initiale du point

	SpaceShip ship(&window, windowHeight, windowWidth, windowWidth / 2, windowHeight / 1.2, "Green");
	bool shipDestroyed = false;
	// Monster mons(&window, windowHeight, windowWidth, windowWidth / 3, windowHeight / 3, "Green");
	int numberOfLine = 4;
	MonsterLine *mons[4];
	mons[0] = new MonsterLine(&window, windowHeight, windowWidth, windowWidth / 5, windowHeight / 3, 10, "Green");
	mons[1] = new MonsterLine(&window, windowHeight, windowWidth, windowWidth / 2, windowHeight / 4, 15, "Green");
	mons[2] = new MonsterLine(&window, windowHeight, windowWidth, windowWidth / 2, windowHeight / 6, 11, "Green");
	mons[3] = new MonsterLine(&window, windowHeight, windowWidth, windowWidth / 2, windowHeight / 5, 4, "Green");

	bool *explosion[] = {nullptr, nullptr, nullptr, nullptr};
	bool change = false;

	sf::Clock clockCommand;
	sf::Clock clockProjectile;
	sf::Clock clockShoot;
	sf::Clock clockMonster;
	sf::Clock clockExplosion;
	sf::Time delayCommand = sf::milliseconds(20);
	sf::Time delayProjectile = sf::milliseconds(10);
	sf::Time delayMonster = sf::milliseconds(50);
	sf::Time delayShoot = sf::milliseconds(100);
	sf::Time delayExplosion = sf::milliseconds(300 / 5);
	sf::Event event;

	while (window.isOpen())
	{
		while (!shipDestroyed && window.isOpen())
		{
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			if (clockCommand.getElapsedTime() >= delayCommand)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					try
					{
						ship.xAdd();
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
						ship.xSub();
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
						ship.yAdd();
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
						ship.ySub();
					}
					catch (SpaceShip::Exept exp)
					{
#ifdef VERBOSE_MAIN
						cout << exp.message << endl;
#endif
					}
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
				{
#ifdef VERBOSE_MAIN
					cout << "E pressed" << endl;
#endif
					// explosion = true;
				}
				for (int j = 0; j < numberOfLine; j++)
				{
					mons[j]->updateCollision(ship, &(explosion[j]));
				}
				shipDestroyed = ship.detectImpact(mons, numberOfLine);

				clockCommand.restart(); // Redémarre l'horloge pour le prochain intervalle
			}

			if (clockShoot.getElapsedTime() >= delayShoot)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					ship.shoot();
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
				}
				clockShoot.restart(); // Redémarre l'horloge pour le prochain intervalle
			}

			if (clockProjectile.getElapsedTime() >= delayProjectile)
			{
				ship.updateProjectiles();
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

			// mons.explosion();
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
							cout << exp.message << endl;
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
							cout << exp.message << endl;
						}
					}

					if (change)
					{
						mons[j]->changeDirection();
						change = false;
					}
				}

				clockMonster.restart();
			}

			if (mons[0] != nullptr)
			{
				cout << (mons[0])[0].getDirection() << endl;
				Monster &temp = (*mons[0])[0];
				cout << "Elapsed Time for Explosion: " << temp.getElapsedTimeClockExplosion().asMilliseconds() << " ms" << endl;
				cout << "Position X: " << temp.getX() << endl;
			}

			for (int j = 0; j < numberOfLine; j++)
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
							cout << "Monster " << i << " in line " << j << " exploded." << endl;
							clockExplosion.restart(); // Only reset timer when an explosion starts
						}
					}
				}
			}

			// Efface l'écran en blanc
			window.clear(sf::Color::White);
			window.draw(ship);
			for (int j = 0; j < numberOfLine; j++)
			{
				for (int i = 0; i < mons[j]->getNumberOfMonster(); i++)
				{
					window.draw((*mons[j])[i]);
				}
			}
			window.display();
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	cout << "Window closed" << endl;

	for (int j = 0; j < numberOfLine; j++)
	{
		delete mons[j];
	}

	return 0;
}
