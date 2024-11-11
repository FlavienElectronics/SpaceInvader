#include "main.hpp"

// #define VERBOSE_MAIN

using namespace std;

class MonsterLine
{
private:
	int direction;
	Monster **block;
	int numberOfMonster;

	sf::RenderWindow *window;
	float winHeight;
	float winWidth;

public:
	class Exept
	{
	public:
		std::string message;
		Exept(std::string mes)
		{
			this->message = mes;
		}
	};

	MonsterLine(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, int numberOfMonster, string color)
	{
		cout << "Constructeur MonsterLine" << endl;
		this->direction = rand() % 2;
		this->numberOfMonster = numberOfMonster;
		this->winHeight = windowHeight;
		this->winWidth = windowWidth;
		block = new Monster *[this->numberOfMonster];
		int xLocation = 10;
		int yLocation = 10;
		if (this->block != nullptr)
		{
			for (int i = 0; i < this->numberOfMonster; i++)
			{
				block[i] = new Monster(win, winHeight, winWidth, xLocation * (i + 1) * 5, yLocation * i * 4, "col");

				// cout << block[i] << endl;
			}
		}
	}

	Monster &operator[](int location)
	{
		return (*this->block[location]);
	}

	void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		for (int i = 0; i < this->numberOfMonster; i++)
		{
			if (this->block[i] != nullptr)
			{
				target.draw(*this->block[i], states);
			}
		}
	}

	bool *updateCollision(const SpaceShip &ship)
	{
		bool *monsterTouched = new bool[this->numberOfMonster];
		for (int i = 0; i < this->numberOfMonster; i++)
		{
			monsterTouched[i] = this->block[i]->updateCollision(ship);
		}
		return (monsterTouched);
	}

	void xSub()
	{
		for (int j = 0; j < this->numberOfMonster; j++)
		{
			if (this->block[j]->x < 0)
			{
				this->block[j]->x = 0;
				throw(Exept("x out of bound < 0"));
			}
			else
			{
				for (int i = 0; i < this->block[j]->numberOfPixels; i++)
				{
					this->block[j]->pt[i]->xSub();
				}
			}
		}
	}

	void xAdd()
	{
		for (int j = 0; j < this->numberOfMonster; j++)
		{
			if (this->block[j]->x > winWidth - this->block[j]->xSize)
			{
				this->block[j]->x = winWidth - this->block[j]->xSize;
				throw(Exept("x out of bound > width"));
			}
			else
			{
				for (int i = 0; i < this->block[j]->numberOfPixels; i++)
				{
					this->block[j]->pt[i]->xAdd();
				}
			}
		}
	}

	int getDirection()
	{
		return (this->direction);
	}

	int getNumberOfMonster()
	{
		return (this->numberOfMonster);
	}
};

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

	SpaceShip ship(&window, windowHeight, windowWidth, windowWidth / 2, windowHeight / 2, "Green");
	// Monster mons(&window, windowHeight, windowWidth, windowWidth / 3, windowHeight / 3, "Green");
	MonsterLine mons(&window, windowHeight, windowWidth, windowWidth / 3, windowHeight / 3, 2, "Green");

	bool *explosion;

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
				// explosion = true;
			}

			explosion = mons.updateCollision(ship);

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
			for (int i = 0; i < mons.getNumberOfMonster(); i++)
			{
				if (mons.getDirection() == 0) // go left
				{
					try
					{
						mons.xSub();
					}
					catch (Monster::Exept exp)
					{
						// mons.changeDirection();
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
						// mons.changeDirection();
					}
				}
			}
			clockMonster.restart();
		}
		/*
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
				*/

		// Efface l'écran en blanc
		window.clear(sf::Color::White);
		window.draw(ship);
		for (int i = 0; i < mons.getNumberOfMonster(); i++)
		{
			window.draw(mons[i]);
		}
		window.display();
	}
	cout << "Window closed" << endl;

	return 0;
}
