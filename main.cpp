#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define VERBOSE

using namespace std;

class SpaceShip;
class Point;

class Point : public sf::RectangleShape
{
private:
	float x, y;
	int size;
	string color;

public:
	Point()
	{
		this->x = -1;
		this->y = -1;
		this->color = "Invisible";
	}

	Point(float x, float y, int size, string color) : sf::RectangleShape(sf::Vector2f(1, 1))
	{
		this->x = x;
		this->y = y;
		this->size = size;
		this->color = color;

		this->setFillColor(sf::Color::Black);
		this->setPosition(x, y);
	}

	void xAdd()
	{
		this->x++;
		this->setPosition(x, y);
	}
	void yAdd()
	{
		this->y++;
		this->setPosition(x, y);
	}
	void xSub()
	{
		this->x--;
		this->setPosition(x, y);
	}
	void ySub()
	{
		this->y--;
		this->setPosition(x, y);
	}
};

/* Projectile généralisable avec SpaceShip ???*/
class Projectile : public sf::Drawable
{
private:
	int numberOfPixels;
	Point *pt[2];
	float x, y;

public:
	Projectile(float x_pos, float y_pos, string color) : x(x_pos), y(y_pos), numberOfPixels(2)
	{
		pt[0] = new Point(x + 0, y + 0, 1, color);
		pt[1] = new Point(x + 0, y + 1, 1, color);
	}

	void ySub()
	{
		this->y--;
		pt[0]->ySub();
		pt[1]->ySub();
	}

	// Vérifie si le projectile est en dehors de la fenêtre
	bool isOutOfBounds(float windowHeight)
	{
		return this->y < 0; // Un projectile est hors de l'écran si sa position Y est inférieure à 0
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
	{
		for (int i = 0; i < 2; i++)
		{
			target.draw(*pt[i], states);
		}
	}

	float getY() const
	{
		return y;
	}

	~Projectile()
	{
		for (int i = 0; i < numberOfPixels; i++)
		{
			if (pt[i] != nullptr)
			{
#ifdef VERBOSE
				cout << "Destruction point " << i << " projectile" << endl;
#endif
			}
		}
	}
};

/*Faire une classe Player*/
class SpaceShip : public sf::Drawable
{
protected:
	float x, y;
	Point **pt;
	Projectile **pjt; /*Utilisation de la STL pour les projectile (vector)*/
	int numberOfPixels;
	int numberOfProjectiles;
	int xSize;
	int ySize;

	sf::RenderWindow *window;
	float winHeight;
	float winWidth;

public:
	class Exept
	{
	public:
		string message;
		Exept(string mes)
		{
			this->message = mes;
		}
	};

	SpaceShip() : x(0), y(0), numberOfPixels(11) {}

	SpaceShip(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, string color) : x(x_pos), y(y_pos), numberOfPixels(11), numberOfProjectiles(50), xSize(5), ySize(4)
	{
#ifdef VERBOSE
		cout << "Creation ship nb pixels " << numberOfPixels << endl;
#endif
		pt = new Point *[numberOfPixels];
		pjt = new Projectile *[numberOfProjectiles];
		pt[0] = new Point(x + 2, y + 0, 1, color);
		pt[1] = new Point(x + 1, y + 1, 1, color);
		pt[2] = new Point(x + 2, y + 1, 1, color);
		pt[3] = new Point(x + 3, y + 1, 1, color);
		pt[4] = new Point(x + 0, y + 2, 1, color);
		pt[5] = new Point(x + 1, y + 2, 1, color);
		pt[6] = new Point(x + 2, y + 2, 1, color);
		pt[7] = new Point(x + 3, y + 2, 1, color);
		pt[8] = new Point(x + 4, y + 2, 1, color);
		pt[9] = new Point(x + 1, y + 3, 1, color);
		pt[10] = new Point(x + 3, y + 3, 1, color);
		this->window = win;
		this->winHeight = windowHeight;
		this->winWidth = windowWidth;
		for (int i = 0; i < numberOfProjectiles; i++)
		{
			this->pjt[i] = nullptr;
		}
	}

	void shoot()
	{
		// Chercher un emplacement libre dans le tableau de projectiles
		for (int i = 0; i < numberOfProjectiles; ++i)
		{
			if (pjt[i] == nullptr) // Si l'emplacement est libre
			{
				pjt[i] = new Projectile(this->x + 2, this->y - 2, "col");
#ifdef VERBOSE
				cout << "Lancement projectile " << i << endl;
#endif
				break;
			}
		}
	}

	void updateProjectiles()
	{
		for (int i = 0; i < numberOfProjectiles; ++i)
		{
			if (pjt[i] != nullptr)
			{
				// Déplacer le projectile vers le haut
				pjt[i]->ySub();

				// Vérifier si le projectile est en dehors de l'écran
				if (pjt[i]->isOutOfBounds(this->winHeight))
				{
					// Libérer la mémoire du projectile
					delete pjt[i];
					pjt[i] = nullptr;
#ifdef VERBOSE
					cout << "Destruction projectile " << i << endl;
#endif
				}
			}
		}
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
	{
		// Dessiner tous les points du vaisseau
		for (int i = 0; i < numberOfPixels; i++)
		{
			target.draw(*pt[i], states);
		}

		// Dessiner tous les projectiles
		for (int i = 0; i < numberOfProjectiles; ++i)
		{
			if (pjt[i] != nullptr)
			{
				target.draw(*pjt[i], states);
			}
		}
	}

	void xAdd()
	{
		this->x++;
		if (this->x > winWidth - this->xSize)
		{
			this->x = winWidth - this->xSize;
			throw(Exept("x out of bound > width"));
		}
		else
		{
			for (int i = 0; i < numberOfPixels; i++)
			{
				pt[i]->xAdd();
			}
#ifdef VERBOSE
			cout << "New pos : " << this->x << ";" << this->y << endl;
#endif
		}
	}
	void yAdd()
	{
		this->y++;
		if (this->y > winHeight - this->ySize)
		{
			this->y = winHeight - this->ySize;
			throw(Exept("y out of bound y > height"));
		}
		else
		{
			for (int i = 0; i < numberOfPixels; i++)
			{
				pt[i]->yAdd();
			}
#ifdef VERBOSE
			cout << "New pos : " << this->x << ";" << this->y << endl;
#endif
		}
	}
	void xSub()
	{
		this->x--;
		if (this->x < 0)
		{
			this->x = 0;
			throw(Exept("x out of bound < 0"));
		}
		else
		{
			for (int i = 0; i < numberOfPixels; i++)
			{
				pt[i]->xSub();
			}
#ifdef VERBOSE
			cout << "New pos : " << this->x << ";" << this->y << endl;
#endif
		}
	}
	void ySub()
	{
		this->y--;
		if (this->y < 0)
		{
			this->y = 0;
			throw(Exept("y out of bound y < 0"));
		}
		else
		{
			for (int i = 0; i < numberOfPixels; i++)
			{
				pt[i]->ySub();
			}
#ifdef VERBOSE
			cout << "New pos : " << this->x << ";" << this->y << endl;
#endif
		}
	}

	~SpaceShip()
	{
#ifdef VERBOSE
		cout << typeid(this).name() << " Nombre de pixels vaisseau " << numberOfPixels << endl;
		cout << typeid(this).name() << " Nombre de projectile vaisseau " << numberOfProjectiles << endl;
#endif
		if (pt != nullptr)
		{
			for (int i = 0; i < numberOfPixels; i++)
			{
				if (pt[i] != nullptr)
				{
					delete pt[i]; // Libérer la mémoire allouée pour chaque Point
#ifdef VERBOSE
					cout << "Destruction point vaisseau " << i << endl;
#endif
				}
			}
			delete[] pt;
			pt = nullptr;
		}
#ifdef VERBOSE
		cout << "Allons détruire les projectiles du vaisseau" << endl;
#endif
		if (pjt != nullptr)
		{
			for (int i = 0; i < numberOfProjectiles; i++)
			{
				if (pjt[i] != nullptr)
				{
					delete pjt[i]; // Libérer chaque projectile si il est alloué
#ifdef VERBOSE
					cout << "Destruction point vaisseau " << i << endl;
#endif
				}
			}
			delete[] pjt;
			pjt = nullptr;
		}
	}
};

class Monster : public SpaceShip
{

protected:
	int direction; // 0 -> goes left | 1 -> goes right

public:
	Monster(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, string color)
	{
		srand(time(0));
		this->direction = rand() % 2;

		this->x = x_pos;
		this->y = y_pos;
		this->numberOfPixels = 10;
		this->numberOfProjectiles = 10;
		this->xSize = 5;
		this->ySize = 4;

		pt = new Point *[numberOfPixels];
		pjt = new Projectile *[numberOfProjectiles];

		pt[0] = new Point(x + 1, y + 0, 1, color);
		pt[1] = new Point(x + 3, y + 0, 1, color);
		pt[2] = new Point(x + 0, y + 1, 1, color);
		pt[3] = new Point(x + 2, y + 1, 1, color);
		pt[4] = new Point(x + 4, y + 1, 1, color);
		pt[5] = new Point(x + 1, y + 2, 1, color);
		pt[6] = new Point(x + 2, y + 2, 1, color);
		pt[7] = new Point(x + 3, y + 2, 1, color);
		pt[8] = new Point(x + 1, y + 3, 1, color);
		pt[9] = new Point(x + 3, y + 3, 1, color);
		this->window = win;
		this->winHeight = windowHeight;
		this->winWidth = windowWidth;
		for (int i = 0; i < numberOfProjectiles; i++)
		{
			this->pjt[i] = nullptr;
		}
#ifdef VERBOSE
		cout << "Creation monster nb pixels " << numberOfPixels << " Sens : " << this->direction << endl;
#endif
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
	{
		// Dessiner tous les points du vaisseau
		for (int i = 0; i < numberOfPixels; i++)
		{
			target.draw(*pt[i], states);
		}

		// Dessiner tous les projectiles
		for (int i = 0; i < 10; i++)
		{
			if (pjt[i] != nullptr)
			{
				target.draw(*pjt[i], states);
			}
		}
	}

	int getDirection()
	{
		return (this->direction);
	}

	~Monster()
	{
#ifdef VERBOSE
		cout << typeid(this).name() << " Nombre de pixels monstre " << numberOfPixels << endl;
		cout << typeid(this).name() << " Nombre de projectile monstre " << numberOfProjectiles << endl;
		cout << "Fin destructeur monster " << endl;
#endif
	}
};

int main()
{
	const string gameName = "SpaceInvader";
	const float windowWidth = 500;
	const float windowHeight = 200;

	// Création de la fenêtre SFML
	cout << "Window creation" << endl;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), gameName);

	float x = windowWidth / 2, y = windowHeight / 2; // Position initiale du point

	SpaceShip ship(&window, windowHeight, windowWidth, windowWidth / 2, windowHeight / 2, "Green");
	Monster mons(&window, windowHeight, windowWidth, windowWidth / 3, windowHeight / 3, "Green");

	sf::Clock clockCommand;
	sf::Clock clockProjectile;
	sf::Clock clockShoot;
	sf::Clock clockMonster;
	sf::Time delayCommand = sf::milliseconds(20);
	sf::Time delayProjectile = sf::milliseconds(10);
	sf::Time delayMonster = sf::milliseconds(50);
	sf::Time delayShoot = sf::milliseconds(100);

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
#ifdef VERBOSE
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
#ifdef VERBOSE
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
#ifdef VERBOSE
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
#ifdef VERBOSE
					cout << exp.message << endl;
#endif
				}
			}

			clockCommand.restart(); // Redémarre l'horloge pour le prochain intervalle
		}

		if (clockShoot.getElapsedTime() >= delayShoot)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				ship.shoot();
			clockShoot.restart(); // Redémarre l'horloge pour le prochain intervalle
		}

		// Efface l'écran en blanc
		window.clear(sf::Color::White);

		window.draw(ship);
		window.draw(mons);

		if (clockProjectile.getElapsedTime() >= delayProjectile)
		{
			ship.updateProjectiles();
			clockProjectile.restart();
		}

		if (clockMonster.getElapsedTime() >= delayMonster)
		{
			if (mons.getDirection() == 0) // go left
			{
				mons.xSub();
			}
			else if (mons.getDirection() == 1) // go right
			{
				mons.xAdd();
			}
			clockMonster.restart();
		}

		// Affiche la mise à jour de la fenêtre
		window.display();
	}
	cout << "Window closed" << endl;

	return 0;
}
