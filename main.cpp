#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace std;

class Point : public sf::CircleShape
{
			
	private:
		float x,y;
		int size;
		string color;
	public:
		Point(float x,float y,int size,string color) : sf::CircleShape(size)
		{
			this->x = x;
			this->y = y;
			this->size = size;
			this->color = color;
			
			this->setFillColor(sf::Color::Green);
			this->setPosition(x,y);
		}
		void xAdd()
		{
			this->x++;
			this->setPosition(x,y);
		}
		void yAdd()
		{
			this->y++;
			this->setPosition(x,y);
		}
};

class SpaceShip : public sf::CircleShape
{
	private :
		Point* p;
	public :
		SpaceShip(float x_pos, float y_pos, string color)
		{
			p = new Point(x_pos,y_pos,1,"Col");	
		}
};
			

int main() {


    const string gameName = "SpaceInvader";
    const float windowWidth = 1000;
    const float windowHeight = 562;

    // Création de la fenêtre SFML
    cout << "Window creation" << endl;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), gameName);

    sf::CircleShape point(2); // Point avec un rayon de 2 pixels
    point.setFillColor(sf::Color::Red); // Couleur du point

    float x = windowWidth/2, y = windowHeight/2; // Position initiale du point
    point.setPosition(x, y);
    
    Point p2(100,100,2,"Vert");
    SpaceShip ship(200,100,"Green");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Exemple de déplacement du point
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
        {
        x += 1;
        p2.xAdd();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {x -= 1;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {y += 1;}
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {y -= 1; p2.yAdd();}
        
         // Empêcher le point de sortir des bords de la fenêtre
        if (x < 0) x = 0;
        if (x > windowWidth - 2 * point.getRadius()) x = windowWidth - 2 * point.getRadius();
        if (y < 0) y = 0;
        if (y > windowHeight - 2 * point.getRadius()) y = windowHeight - 2 * point.getRadius();

        // Mise à jour de la position du point
        point.setPosition(x, y);

        // Efface l'écran en blanc
        window.clear(sf::Color::White);

        // Dessine le point uniquement à la nouvelle position
        window.draw(point);
        window.draw(p2);
        window.draw(ship);

        // Affiche la mise à jour de la fenêtre
        window.display();
    }
    cout << "Window closed" << endl;

    return 0;
}
