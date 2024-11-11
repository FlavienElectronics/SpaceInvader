#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
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
				cout << "Destruction point " << i << " projectile" << endl;
			}
		}
	}
};

class SpaceShip : public sf::Drawable
{

protected:
	Point **pt;
	Projectile **pjt;
	sf::RenderWindow *window;
	int numberOfPixels;
	int numberOfProjectiles;
	float winHeight;
	float x, y;

	void correctPosition()
	{
		/*
				if (this->x < 0)
			this->x = 0;
		if (this->x > windowWidth - 2 * point.getRadius())
			this->x = windowWidth - 2 * point.getRadius();
		if (this->y < 0)
			this->y = 0;
		if (this->y > windowHeight - 2 * this->getRadius())
			this->y = windowHeight - 2 * point.getRadius();
			*/
	}

public:
	SpaceShip() : x(0), y(0), numberOfPixels(11) {}

	SpaceShip(sf::RenderWindow *win, float windowHeight, float x_pos, float y_pos, string color) : x(x_pos), y(y_pos), numberOfPixels(11), numberOfProjectiles(50)
	{
		cout << "Creation ship nb pixels " << numberOfPixels << endl;
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
		for (int i = 0; i < numberOfProjectiles; i++)
		{
			this->pjt[i] = nullptr;
		}
	}

	void shoot()
	{
		// Chercher un emplacement libre dans le tableau de projectiles
		for (int i = 0; i < 50; ++i)
		{
			if (pjt[i] == nullptr) // Si l'emplacement est libre
			{
				pjt[i] = new Projectile(this->x + 2, this->y - 5, "col");
				cout << "Lancement projectile " << i << endl;
				break;
			}
		}
	}

	void updateProjectiles()
	{
		for (int i = 0; i < 50; ++i)
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
					cout << "Destruction projectile " << i << endl;
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
		for (int i = 0; i < 50; ++i)
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
		for (int i = 0; i < 11; i++)
		{
			pt[i]->xAdd();
		}
	}
	void yAdd()
	{
		this->y++;
		for (int i = 0; i < 11; i++)
		{
			pt[i]->yAdd();
		}
	}
	void xSub()
	{
		this->x--;
		for (int i = 0; i < 11; i++)
		{
			pt[i]->xSub();
		}
	}
	void ySub()
	{
		this->y--;
		for (int i = 0; i < 11; i++)
		{
			pt[i]->ySub();
		}
	}

	~SpaceShip()
	{
		cout << typeid(this).name() << " Nombre de pixels vaisseau " << numberOfPixels << endl;
		cout << typeid(this).name() << " Nombre de projectile vaisseau " << numberOfProjectiles << endl;
		if (pt != nullptr)
		{
			for (int i = 0; i < numberOfPixels; i++)
			{
				if (pt[i] != nullptr)
				{
					delete pt[i]; // Libérer la mémoire allouée pour chaque Point
					cout << "Destruction point vaisseau " << i << endl;
				}
			}
			delete [] pt;
		}
		cout << "Allons détruire les projectiles du vaisseau" << endl;
		if (pjt != nullptr)
		{
			for (int i = 0; i < numberOfProjectiles; i++)
			{
				if (pjt[i] != nullptr)
				{
					delete pjt[i]; // Libérer chaque projectile si il est alloué
					cout << "Destruction point vaisseau " << i << endl;
				}
			}
			delete[] pjt;
		}
	}
};

class Monster : public SpaceShip
{
private:
	Point *pt[10];
	Projectile *pjt[10];

public:
	// Monster(sf::RenderWindow *win, float windowHeight, float x_pos, float y_pos, string color) : SpaceShip(win,windowHeight,x_pos,y_pos,color);
	//~Monster();

	Monster(sf::RenderWindow *win, float windowHeight, float x_pos, float y_pos, string color)
	{
		this->x = x_pos;
		this->y = y_pos;
		this->numberOfPixels = 10;
		this->numberOfProjectiles = 10;

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
		for (int i = 0; i < numberOfProjectiles; i++)
		{
			this->pjt[i] = nullptr;
		}
		cout << "Creation monster nb pixels " << numberOfPixels << endl;
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

	~Monster()
	{
		cout << typeid(this).name() << " Nombre de pixels monstre " << numberOfPixels << endl;
		cout << typeid(this).name() << " Nombre de projectile monstre " << numberOfProjectiles << endl;

		/*for (int i = 0; i < numberOfPixels; i++)
		{
			if (pt[i] != nullptr)
			{
				delete pt[i]; // Libérer la mémoire des points du monstre
				cout << "Destruction du point monster " << i << endl;
			}
		}

		cout << "Allons détruire les projectiles du monstre" << endl;
		for (int i = 0; i < 10; i++)
		{
			if (pjt[i] != nullptr)
			{
				delete pjt[i]; // Libérer chaque projectile si il est alloué
				cout << "Destruction du projectile monster " << i << endl;
			}
		}
		*/
		cout << "Fin destructeur monster " << endl;
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

	Monster mons(&window, windowHeight, windowWidth / 3, windowHeight / 3, "Green");
	SpaceShip ship(&window, windowHeight, windowWidth / 2, windowHeight / 2, "Green");

	sf::Clock clock;
	sf::Clock clockProjectile;
	sf::Clock clockShoot;
	sf::Time delay = sf::milliseconds(20);
	sf::Time delayProjectile = sf::milliseconds(10);
	sf::Time delayShoot = sf::milliseconds(100);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (clock.getElapsedTime() >= delay)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				ship.xAdd();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				ship.xSub();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				ship.yAdd();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				ship.ySub();

			clock.restart(); // Redémarre l'horloge pour le prochain intervalle
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
		// window.draw(mons);

		if (clockProjectile.getElapsedTime() >= delayProjectile)
		{
			ship.updateProjectiles();
			clockProjectile.restart();
		}

		// Affiche la mise à jour de la fenêtre
		window.display();
	}
	cout << "Window closed" << endl;

	return 0;
}
