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
        // Manejar el error de manera más adecuada, por ejemplo, continuar sin música
    } else {
        musica.setLoop(true); // Repetir la música en bucle
        musica.play();
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                int x = event.mouseButton.x / 200;
                int y = event.mouseButton.y / 200;

                if (tablero.marcarCasilla(x, y, jugadorActual->getSimbolo())) {
                    if (tablero.verificarVictoria(jugadorActual->getSimbolo())) {
                        std::cout << "Jugador " << jugadorActual->getSimbolo() << " gana!" << std::endl;
                        window.close();
                    } else if (tablero.estaLleno()) {
                        std::cout << "Empate!" << std::endl;
                        window.close();
                    } else {
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