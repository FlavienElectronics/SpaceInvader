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
	Point *pt[2];
	float x, y;

public:
	Projectile(float x_pos, float y_pos, string color) : x(x_pos), y(y_pos)
	{
		pt[0] = new Point(x + 0, y + 0, 1, color);
		pt[1] = new Point(x + 0, y + 1, 1, color);
	}

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
	{
		for (int i = 0; i < 2; i++)
		{
			target.draw(*pt[i], states); 
		}
	}
};

class SpaceShip : public sf::Drawable
{
private:
	Point *pt[11];
	Projectile * pjt[50];
	float x, y;

public:
	SpaceShip(float x_pos, float y_pos, string color) : x(x_pos), y(y_pos)
	{
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
	}

	// Surcharge de la fonction `draw` pour dessiner les Points de SpaceShip
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override
	{
		for (int i = 0; i < 11; i++)
		{
			target.draw(*pt[i], states); // Dessiner chaque Point du vaisseau
		}
	}

	void shoot()
	{
		pjt[0] = new Projectile(this->x + 2 , this->y -5 , "col");
		cout << "space" << endl;
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
		for (int i = 0; i < 11; i++)
		{
			delete pt[i]; // Libérer la mémoire allouée pour chaque Point
		}
	}
};

int main()
{
	const string gameName = "SpaceInvader";
	const float windowWidth = 1000;
	const float windowHeight = 562;

	// Création de la fenêtre SFML
	cout << "Window creation" << endl;
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), gameName);

	sf::CircleShape point(2);			// Point avec un rayon de 2 pixels
	point.setFillColor(sf::Color::Red); // Couleur du point

	float x = windowWidth / 2, y = windowHeight / 2; // Position initiale du point
	point.setPosition(x, y);

	Point p2(100, 100, 1, "Vert");
	SpaceShip ship(200, 100, "Green");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Exemple de déplacement du point
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			ship.shoot();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			x += 1;
			p2.xAdd();
			ship.xAdd();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			x -= 1;
			p2.xSub();
			ship.xSub();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			y += 1;
			p2.yAdd();
			ship.yAdd();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			y -= 1;
			p2.ySub();
			ship.ySub();
		}

		// Empêcher le point de sortir des bords de la fenêtre
		if (x < 0)
			x = 0;
		if (x > windowWidth - 2 * point.getRadius())
			x = windowWidth - 2 * point.getRadius();
		if (y < 0)
			y = 0;
		if (y > windowHeight - 2 * point.getRadius())
			y = windowHeight - 2 * point.getRadius();

		// Mise à jour de la position du point
		point.setPosition(x, y);

		// Efface l'écran en blanc
		window.clear(sf::Color::White);

		// Dessine le point et les éléments du vaisseau
		window.draw(point);
		window.draw(p2);
		window.draw(ship);

		// Affiche la mise à jour de la fenêtre
		window.display();
	}
	cout << "Window closed" << endl;

	return 0;
}
