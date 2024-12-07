#include <SFML/Graphics.hpp>
#include <iostream>

const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

int main() {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tres en Raya");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);

        // Aquí puedes agregar el código para dibujar el tablero y los símbolos

        window.display();
    }

    return 0;
}
