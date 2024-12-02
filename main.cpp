#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Jugador.hpp"
#include "Tablero.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Tres en Raya");

    Tablero tablero;
    Jugador jugador1('X');
    Jugador jugador2('O');
    Jugador* jugadorActual = &jugador1;

    // Cargar y reproducir la música de fondo
    sf::Music musica;
    if (!musica.openFromFile("linkin_park.wav")) {
        std::cerr << "Error al cargar la música de fondo linkin_park.wav" << std::endl;
        // Handle error more gracefully, e.g., continue without music
    } else {
        musica.setLoop(true); // Repetir la música en bucle
        musica.play();
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int row = event.mouseButton.y / 200;
                    int col = event.mouseButton.x / 200;
                    if (tablero.marcarCasilla(row, col, jugadorActual->getSimbolo())) {
                        if (tablero.verificarVictoria(jugadorActual->getSimbolo())) {
                            // Mostrar mensaje de victoria
                            window.close();
                        }
                        jugadorActual = (jugadorActual == &jugador1) ? &jugador2 : &jugador1;
                    }
                }
            }
        }

        window.clear();
        tablero.dibujar(window);
        window.display();
    }

    return 0;
}