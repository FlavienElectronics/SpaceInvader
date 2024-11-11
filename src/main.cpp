#include "main.hpp"

// #define VERBOSE_MAIN

using namespace std;

class MonsterLine
{
private:
	Monster **part;
	int numberOfMonster;

	sf::RenderWindow *window;
	float winHeight;
	float winWidth;

public:
	MonsterLine()
	{
		this->numberOfMonster = 5;
		part = new Monster *[this->numberOfMonster];
		int xLoc = 10;
		for (int i = 0; i < this->numberOfMonster; i++)
		{
			// part[i] = new Monster()
		}
	}
};

int main()
{
	const string gameName = "SpaceInvader";
	const float windowWidth = 128;
	const float windowHeight = 96;

	// Création de la fenêtre SFML
	cout << "Window creation" << endl;
	    // Définissez la résolution initiale
    sf::Vector2u resolution(windowWidth, windowHeight);
    // Créez une fenêtre avec une taille agrandie
    sf::RenderWindow window(sf::VideoMode(resolution.x * 6, resolution.y * 6), gameName);
    // Créez une vue qui correspond à la résolution de départ
    sf::View view(sf::FloatRect(0, 0, resolution.x, resolution.y));
    // Appliquez l’échelle à la vue (par exemple, x2 pour doubler la taille)
    view.setViewport(sf::FloatRect(0, 0, 1, 1)); // Fenêtre entière
    window.setView(view);
	float x = windowWidth / 2, y = windowHeight / 2; // Position initiale du point

	SpaceShip ship(&window, windowHeight, windowWidth, windowWidth / 2, windowHeight / 2, "Green");
	Monster mons(&window, windowHeight, windowWidth, windowWidth / 3, windowHeight / 3, "Green");

	sf::Clock clockCommand;
	sf::Clock clockProjectile;
	sf::Clock clockShoot;
	sf::Clock clockMonster;
	sf::Clock clockExplosion;
	sf::Time delayCommand = sf::milliseconds(20);
	sf::Time delayProjectile = sf::milliseconds(10);
	sf::Time delayMonster = sf::milliseconds(50);
	sf::Time delayShoot = sf::milliseconds(100);
	sf::Time delayExplosion = sf::milliseconds(300);

	bool explosion = false;

	while (window.isOpen())
	{
		sf::Event event;
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
				explosion = true;
			}

			if(mons.updateCollision(ship))
			{
				explosion = true;
			}

			clockCommand.restart(); // Redémarre l'horloge pour le prochain intervalle
		}

		if (clockShoot.getElapsedTime() >= delayShoot)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				ship.shoot();
			clockShoot.restart(); // Redémarre l'horloge pour le prochain intervalle
		}

		if (clockProjectile.getElapsedTime() >= delayProjectile)
		{
			ship.updateProjectiles();
			clockProjectile.restart();
		}

		// mons.explosion();
		if (clockMonster.getElapsedTime() >= delayMonster)
		{
			if (mons.getDirection() == 0) // go left
			{
				try
				{
					mons.xSub();
				}
				catch (Monster::Exept exp)
				{
					mons.changeDirection();
				}
			}
			else if (mons.getDirection() == 1) // go right
			{
				try
				{
					mons.xAdd();
				}
				catch (Monster::Exept exp)
				{
					mons.changeDirection();
				}
			}
			clockMonster.restart();
		}

		if (clockExplosion.getElapsedTime() >= delayExplosion)
		{
			if (mons.isExplosing())
			{
				cout << "is explosing" << endl;
				mons.updateParticule();
				clockExplosion.restart();
			}
		}

		if (explosion && mons.isAlive())
		{
			mons.explode();
			cout << "explosion" << endl;
			clockExplosion.restart();
		}

		// Efface l'écran en blanc
		window.clear(sf::Color::White);
		window.draw(ship);
		window.draw(mons);
		window.display();
	}
	cout << "Window closed" << endl;

	return 0;
}
