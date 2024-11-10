#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace std;

int main() {


    const string gameName = "SpaceInvader";
    const float windowWidth = 1000;
    const float windowHeight = 562;

    // Création de la fenêtre SFML
    cout << "Window creation" << endl;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), gameName);

    sf::CircleShape point(2); // Point avec un rayon de 2 pixels
    point.setFillColor(sf::Color::Red); // Couleur du point

    float x = 400, y = 300; // Position initiale du point
    point.setPosition(x, y);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Exemple de déplacement du point
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) x += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) x -= 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) y += 1;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) y -= 1;
        
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

        // Affiche la mise à jour de la fenêtre
        window.display();
    }
    cout << "Window closed" << endl;

    return 0;
}
